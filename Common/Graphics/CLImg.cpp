#include "CLImg.h"

#include <string>

using namespace Common;
using namespace Common::Graphics;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

static bool inited = false;
static std::vector<cl_device_id> computeDevices;
static cl_context context;
static cl_command_queue queue;

static const cl_image_format imageFormat = {
		CL_ARGB,
		CL_UNSIGNED_INT8,
};

bool CLImg::SetupCL() {
	if (inited) {
		return true;
	}
	cl_platform_id platforms[64];
	unsigned int platformCount;
	cl_int platformResult = clGetPlatformIDs(64, platforms, &platformCount);
	if (platformResult != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to get platform ids for OpenCL");
		return false;
	}
	for (int i = 0; i < platformCount; ++i) {
		cl_device_id devices[64];
		unsigned int deviceCount;
		cl_int deviceResult = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 64, devices, &deviceCount);
		if (deviceResult == CL_SUCCESS) {
			for (int j = 0; j < deviceCount; ++j) {
				char vendorName[256];
				size_t vendorNameLength;

				size_t maxImgDim[] = {0, 0};
				size_t dimLen = 0;

				cl_int deviceInfoResult = clGetDeviceInfo(devices[j], CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t), &maxImgDim[0], &dimLen);
				deviceInfoResult = clGetDeviceInfo(devices[j], CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t), &maxImgDim[1], &dimLen);
				deviceInfoResult = clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 256, vendorName, &vendorNameLength);
				if (deviceInfoResult == CL_SUCCESS) {
					std::string sVendorName = vendorName;
					if (sVendorName.find("NVIDIA") != std::string::npos || sVendorName.find("AMD") != std::string::npos || sVendorName.find("Advanced Micro Devices") != std::string::npos) {
						computeDevices.push_back(devices[j]);
						break;
					}
				}
			}
		}
	}

	cl_int contextResult;
	context = clCreateContext(nullptr, 1, &computeDevices[0], nullptr, nullptr, &contextResult);
	if (contextResult != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to create context for OpenCL");
		return false;
	}

	cl_int commandQueueResult;
	queue = clCreateCommandQueue(context, computeDevices[0], 0, &commandQueueResult);
	if (commandQueueResult != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to create queues for OpenCL");
		return false;
	}

	inited = true;
	return true;
}

bool CLImg::StopCL() {
	return true;
}

cl_sampler CLImg::MakeSampler(bool normalized) {
	if (!inited) {
		SetupCL();
	}
	cl_bool cl_normalized = normalized ? CL_TRUE : CL_FALSE;
	cl_int error = CL_SUCCESS;
	cl_sampler sampler = clCreateSampler(context, cl_normalized, CL_ADDRESS_NONE, CL_FILTER_LINEAR, &error);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Couldn't make an OpenCL Sampler: %d (%x)", error, error);
		return 0;
	}
	return sampler;
}

cl_mem CLImg::MakeImage(Image* image) {
	if (!inited) {
		SetupCL();
	}
	size_t width = image->GetWidth();
	size_t height = image->GetHeight();
	std::vector<uint32_t> colorData = image->ColorBytes();
	void* colorBytes = colorData.data();

	cl_int error = CL_SUCCESS;
	cl_mem result = clCreateImage2D(context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		&imageFormat,
		width,
		height,
		width * sizeof(uint32_t),
		colorBytes,
		&error
	);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Couldn't make an OpenCL Image2D buffer from an Image*: %d (%x)", error, error);
		return 0;
	}
	return result;
}

cl_mem CLImg::MakeImage(size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	cl_int error = CL_SUCCESS;
	cl_mem result = clCreateImage2D(context,
		CL_MEM_READ_WRITE,
		&imageFormat,
		width,
		height,
		0,
		nullptr,
		&error);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Couldn't make a blank OpenCL Image2D buffer: %d (%x)", error, error);
		return 0;
	}
	return result;
}

BitmapImage* CLImg::NewImageFromCL(cl_mem image, size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	return NewImageFromCL(image, 0, 0, width, height);
}

BitmapImage* CLImg::NewImageFromCL(cl_mem image, size_t originX, size_t originY, size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	std::vector<uint32_t> resultBytes(width * height);
	size_t origin[3] = { originX, originY, 0 };
	size_t region[3] = { width, height, 1 };
	cl_int error = clEnqueueReadImage(queue, image, CL_TRUE, origin, region, 0, 0, resultBytes.data(), 0, NULL, NULL);
	BitmapImage* result = new BitmapImage(resultBytes, width, height);
	return result;
}

cl_program CLImg::MakeProgram(std::string source) {
	if (!inited) {
		SetupCL();
	}
	cl_int error;
	const char* sourceText = source.c_str();
	cl_program program = clCreateProgramWithSource(context, 1, &sourceText, NULL, &error);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to create OpenCL program with source: %d (%x)", error, error);
		return 0;
	}
	return program;
}

bool CLImg::BuildProgram(cl_program toBuild) {
	if (!inited) {
		SetupCL();
	}
	cl_int error = clBuildProgram(toBuild, 1, &computeDevices[0], NULL, NULL, NULL);
	if (error != CL_SUCCESS) {
		size_t len = 0;
		cl_int logRes = clGetProgramBuildInfo(toBuild, computeDevices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		if (logRes != CL_SUCCESS) {
			Print(LogLevel::ERR, "Failed to size OpenCL build log: %d (%x)", logRes, logRes);
			return false;
		}
		char* buffer = (char*)_malloca(len+1);
		memset(buffer, 0, len + 1);
		logRes = clGetProgramBuildInfo(toBuild, computeDevices[0], CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
		if (logRes != CL_SUCCESS) {
			Print(LogLevel::ERR, "Failed to read OpenCL build log: %d (%x)", logRes, logRes);
			return false;
		}
		Print(LogLevel::ERR, "Failed to build OpenCL program: %s", buffer);
		return false;
	}
	return true;
}

cl_kernel CLImg::MakeKernel(cl_program program, std::string kernelName) {
	if (!inited) {
		SetupCL();
	}
	cl_int error;
	cl_kernel kernel = clCreateKernel(program, kernelName.c_str(), &error);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to create an OpneCL kernel with the name %s: %d (%x)", kernelName.c_str(), error, error);
		return 0;
	}

	return kernel;
}

void CLImg::RunKernel(cl_kernel kernel, size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	cl_int error = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &width, &height, 0, NULL, NULL);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Error executing kernel: %d (%x)", error, error);
	}
}