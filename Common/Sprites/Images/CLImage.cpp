#include "CLImage.h"

#include "../../Logging/Logger.h"

#include <mutex>
#include <string>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;

static bool inited = false;
static std::vector<cl_device_id> computeDevices;
static cl_context context;
static cl_command_queue queue;
static std::mutex clmtx;

#pragma region NativeOpenCL

static const cl_image_format imageFormat = {
		CL_ARGB,
		CL_UNSIGNED_INT8,
};

bool SetupCL() {
	const std::lock_guard<std::mutex> cllock(clmtx);
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

				size_t maxImgDim[] = { 0, 0 };
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

bool StopCL() {
	const std::lock_guard<std::mutex> cllock(clmtx);
	return true;
}


cl_sampler MakeSampler(bool normalized) {
	const std::lock_guard<std::mutex> cllock(clmtx);
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

cl_mem MakeImage(size_t width, size_t height) {
	const std::lock_guard<std::mutex> cllock(clmtx);
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

cl_mem MakeImage(const std::vector<uint32_t>& colors, size_t width, size_t height) {
	const std::lock_guard<std::mutex> cllock(clmtx);
	if (!inited) {
		SetupCL();
	}
	void* colorBytes = (void*)colors.data();
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
		Print(LogLevel::ERR, "Couldn't make an OpenCL Image2D buffer from color bytes: %d (%x)", error, error);
		return 0;
	}
	return result;
}

cl_program MakeProgram(std::string source) {
	const std::lock_guard<std::mutex> cllock(clmtx);
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

bool BuildProgram(cl_program toBuild) {
	const std::lock_guard<std::mutex> cllock(clmtx);
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
		char* buffer = (char*)_malloca(len + 1);
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

cl_kernel MakeKernel(cl_program program, std::string kernelName) {
	const std::lock_guard<std::mutex> cllock(clmtx);
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

void RunKernel(cl_kernel kernel, size_t width, size_t height) {
	const std::lock_guard<std::mutex> cllock(clmtx);
	if (!inited) {
		SetupCL();
	}
	constexpr int work_dim = 2;
	size_t global[work_dim] = { width, height };
	size_t local[work_dim] = { 1, 1 };
	cl_int error = clEnqueueNDRangeKernel(queue, kernel, work_dim, NULL, global, local, 0, NULL, NULL);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Error executing kernel: %d (%x)", error, error);
	}
}
#pragma endregion

CLImage::CLImage()
{
	if (!inited) {
		SetupCL();
	}
	this->gpuImage = 0;
	this->width = 0;
	this->height = 0;
}

CLImage::CLImage(const std::vector<uint32_t>& bmpColors, size_t width, size_t height)
{
	if (!inited) {
		SetupCL();
	}
	this->gpuImage = MakeImage(bmpColors, width, height);
	this->width = width;
	this->height = height;
}

CLImage::CLImage(const std::vector<std::vector<uint32_t>>& bmpColors, size_t width, size_t height)
{
	if (!inited) {
		SetupCL();
	}
	std::vector<uint32_t> colorBytes;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			colorBytes.push_back(bmpColors[x][y]);
		}
	}
	this->gpuImage = MakeImage(colorBytes, width, height);
	this->width = width;
	this->height = height;
}

CLImage::CLImage(cl_mem gpuImage, size_t width, size_t height)
{
	if (!inited) {
		SetupCL();
	}
	this->gpuImage = gpuImage;
	this->width = width;
	this->height = height;
}

CLImage::~CLImage()
{
	if (!inited) {
		SetupCL();
	}
	if (this->gpuImage != 0)
		clReleaseMemObject(this->gpuImage);
}

size_t CLImage::GetWidth()
{
	if (!inited) {
		SetupCL();
	}
	return this->width;
}

size_t CLImage::GetHeight()
{
	if (!inited) {
		SetupCL();
	}
	return this->height;
}

uint32_t CLImage::At(size_t x, size_t y)
{
	if (!inited) {
		SetupCL();
	}
	std::vector<uint32_t> resultBytes(this->GetWidth() * this->GetHeight());
	size_t origin[3] = { x, y, 0 };
	size_t region[3] = { 1, 1, 1 };
	cl_int error = clEnqueueReadImage(queue, this->gpuImage, CL_TRUE, origin, region, 0, 0, resultBytes.data(), 0, NULL, NULL);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to read a color from CL Image: %d (%x)", error, error);
		return 0;
	}
	if (resultBytes.empty()) {
		return 0;
	}
	return resultBytes[0];
}

std::vector<uint32_t> CLImage::ColorBytes()
{
	if (!inited) {
		SetupCL();
	}
	std::vector<uint32_t> resultBytes(this->GetWidth() * this->GetHeight());
	size_t origin[3] = { 0, 0, 0 };
	size_t region[3] = { this->GetWidth(), this->GetHeight(), 1};
	cl_int error = clEnqueueReadImage(queue, this->gpuImage, CL_TRUE, origin, region, 0, 0, resultBytes.data(), 0, NULL, NULL);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to read a color from CL Image: %d (%x)", error, error);
		return std::vector<uint32_t>();
	}
	if (resultBytes.empty()) {
		return std::vector<uint32_t>();
	}
	return resultBytes;
}

CLImage* CLImage::CopyImage() {
	if (!inited) {
		SetupCL();
	}
	return this->CopyImage(this->GetWidth(), this->GetHeight());
}
CLImage* CLImage::CopyImage(size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	return this->CopyImage(0, 0, width, height);
}
CLImage* CLImage::CopyImage(size_t x, size_t y, size_t width, size_t height) {
	if (!inited) {
		SetupCL();
	}
	std::vector<uint32_t> resultBytes(width * height);
	size_t origin[3] = { x, y, 0 };
	size_t region[3] = { width, height, 1 };
	cl_int error = clEnqueueReadImage(queue, this->gpuImage, CL_TRUE, origin, region, 0, 0, resultBytes.data(), 0, NULL, NULL);
	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to create CLImage* from CLImage: %d (%x)", error, error);
		return 0;
	}
	return new CLImage(resultBytes, width, height);
}

bool CLImage::PasteImage(CLImage* other, size_t x, size_t y, int32_t width, int32_t height) {
	if (!inited) {
		SetupCL();
	}
	
	if (width == -1) {
		width = other->GetWidth();
	}
	if (height == -1) {
		height = other->GetHeight();
	}

	size_t src_origin[3] = { 0, 0, 0 };
	size_t src_region[3] = { other->GetWidth(), other->GetHeight(), 0};
	size_t dst_origin[3] = { x, y, 0 };
	size_t dst_region[3] = { width, height, 1 };

	cl_int error = clEnqueueCopyImage(queue, other->gpuImage, this->gpuImage, src_origin, dst_origin, dst_region, 0, nullptr, nullptr);

	if (error != CL_SUCCESS) {
		Print(LogLevel::ERR, "Failed to copy CLImage* on to CLImage: %d (%x)", error, error);
		return false;
	}

	return true;
}

constexpr const char krn_copychannel[] = R"(
uint get_component(uint4 vec, int index)
{
	if(index == 0) return vec.x;
	if(index == 1) return vec.y;
	if(index == 2) return vec.z;
	if(index == 3) return vec.w;
	return 0;
}

void set_component(uint4 vec, int index, uint value)
{
	if(index == 0) vec.x = value;
	if(index == 1) vec.y = value;
	if(index == 2) vec.z = value;
	if(index == 3) vec.w = value;
}

__kernel void copychannel(__read_only image2d_t baseImage, __read_only image2d_t channelImage, __read_only int channel, __write_only image2d_t resultImage)
{
	int2 coord = (int2)(get_global_id(0), get_global_id(1));
	uint4 colorBase = read_imageui(baseImage, coord);
	uint channelNew = get_component(read_imageui(channelImage, coord), channel);
	uint4 mix = (uint4)(channelNew, colorBase.x, colorBase.y, colorBase.z);
	write_imageui(resultImage, coord, mix);
}
)";

bool CLImage::PasteChannel(CLImage* other, int channel)
{
	if (!inited) {
		SetupCL();
	}

	cl_int resultBuff_error;
	cl_mem resultPixels = clCreateImage2D(
		context,
		CL_MEM_READ_WRITE,
		&imageFormat,
		this->GetWidth(),
		this->GetHeight(),
		1,
		nullptr,
		&resultBuff_error
	);

	cl_program copychannel_prg = MakeProgram(krn_copychannel);
	if (BuildProgram(copychannel_prg))
	{
		cl_kernel copychannel_krn = MakeKernel(copychannel_prg, "copychannel");
		cl_int argResult = 0;
		argResult |= clSetKernelArg(copychannel_krn, 0, sizeof(cl_mem), &this->gpuImage);
		argResult |= clSetKernelArg(copychannel_krn, 1, sizeof(cl_mem), &other->gpuImage);
		argResult |= clSetKernelArg(copychannel_krn, 2, sizeof(cl_int), &channel);
		argResult |= clSetKernelArg(copychannel_krn, 3, sizeof(cl_mem), &resultPixels);
		if (argResult != CL_SUCCESS)
		{
			printf("Error: Failed to set kernel arguments! %x (%d)\n", argResult, argResult);
			return false;
		}

		RunKernel(copychannel_krn, this->GetWidth(), this->GetHeight());
		clFinish(queue);

		size_t src_origin[3] = { 0, 0, 0 };
		size_t src_region[3] = { this->GetWidth(), this->GetHeight(), 0 };
		size_t dst_origin[3] = { 0, 0, 0 };
		size_t dst_region[3] = { this->GetWidth(), this->GetHeight(), 1 };
		cl_int error = clEnqueueCopyImage(queue, resultPixels, this->gpuImage, src_origin, dst_origin, dst_region, 0, nullptr, nullptr);
		if (error != CL_SUCCESS) {
			Print(LogLevel::ERR, "Failed to copy CLImage* on to CLImage: %d (%x)", error, error);
			return false;
		}

		return true;
	}

	return false;
}