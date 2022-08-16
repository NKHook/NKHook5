#pragma once

#include "../Logging/Logger.h"
#include "../Sprites/Images/Image.h"
#include "../Sprites/Images/BitmapImage.h"

#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.h>

namespace Common {
	namespace Graphics {
		namespace CLImg {
			using namespace Common;
			using namespace Common::Logging;
			using namespace Common::Logging::Logger;
			using namespace Common::Sprites;
			using namespace Common::Sprites::Images;

			bool SetupCL();
			cl_sampler MakeSampler(bool normalized = false);
			cl_mem MakeImage(Image* image);
			cl_mem MakeImage(size_t width, size_t height);
			BitmapImage* NewImageFromCL(cl_mem clImage, size_t width, size_t height);
			BitmapImage* NewImageFromCL(cl_mem clImage, size_t originX, size_t originY, size_t width, size_t height);
			cl_program MakeProgram(std::string source);
			bool BuildProgram(cl_program toBuild);
			cl_kernel MakeKernel(cl_program program, std::string kernelName);
			template<typename T>
			bool SetKernelArg(cl_kernel kernel, size_t index, T arg) {
				cl_int error = CL_SUCCESS;
				error = clSetKernelArg(kernel, index, sizeof(T), arg);
				if (error != CL_SUCCESS) {
					Print(LogLevel::ERR, "Error occoured whilst setting an OpenCL kernel argument: Index %d", index);
					return false;
				}
				return true;
			}
			void RunKernel(cl_kernel kernel, size_t width, size_t height);
		}
	}
}