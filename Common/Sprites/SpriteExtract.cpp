#include "SpriteExtract.h"
#include "../Files/PngPhoto.h"
#include "../Files/JPngPhoto.h"
#include "../Logging/Logger.h"
#include "../Sprites/Images/MTImage.h"
#include "../Threading/WorkerThread.h"
#include "../Threading/WorkGroup.h"

#include <omp.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Threading;
namespace fs = std::filesystem;

SpriteExtract::SpriteExtract(SpriteTable* table) {
	this->table = table;
}

void SpriteExtract::SetResult(fs::path resultDir)
{
	this->resultDir = resultDir;
}

void SpriteExtract::ExtractAll()
{
	auto& xmls = table->GetXmls();
	fs::path resultDir = this->resultDir;

	omp_set_num_threads(omp_get_max_threads());

#pragma omp parallel for
	for (int64_t i = 0; i < xmls.size(); i++) {
		auto* xmlInfo = xmls[i];
		std::string xmlName = xmlInfo->GetName();
		fs::path xmlOutDir = resultDir / xmlName;

		auto& frames = xmlInfo->GetFrames();
		for (int64_t u = 0; u < frames.size(); u++) {
			auto* frame = frames[u];
			fs::path imagePath = frame->GetImagePath();
			MTImage* image = nullptr;
			JPngPhoto imageFile;
			if (!imageFile.OpenRead(imagePath))
			{
				PngPhoto imageFile;
				imageFile.OpenRead(imagePath);
				image = imageFile.ReadImg();
			}
			else
			{
				image = imageFile.ReadImg();
			}

			if (image->GetHeight() == 0 || image->GetWidth() == 0)
			{
				Print(LogLevel::ERR, "Failed to read image '%s'", imagePath.string().c_str());
				continue;
			}

			for (auto* anim : frame->GetAnimations()) {
				fs::path animOutDir = xmlOutDir / anim->GetName();

				for (auto* cell : anim->GetCells()) {
					fs::path cellFilePath = animOutDir / std::string(cell->GetName() + ".png");
					//Make necessary parent dirs
					fs::create_directories(cellFilePath.parent_path());

					MTImage* splitImage = image->CopyImage(cell->GetX(), cell->GetY(), cell->GetWidth(), cell->GetHeight());
					PngPhoto cellPhoto;
					cellPhoto.OpenWrite(cellFilePath);
					cellPhoto.WriteImg(splitImage);
					cellPhoto.Close();
					delete splitImage;
				}
			}
			for (auto* cell : frame->GetCells()) {
				fs::path cellFilePath = xmlOutDir / std::string(cell->GetName() + ".png");
				//Make necessary parent dirs
				fs::create_directories(cellFilePath.parent_path());

				MTImage* splitImage = image->CopyImage(cell->GetX(), cell->GetY(), cell->GetWidth(), cell->GetHeight());
				PngPhoto cellPhoto;
				cellPhoto.OpenWrite(cellFilePath);
				cellPhoto.WriteImg(splitImage);
				cellPhoto.Close();
				delete splitImage;
			}

			delete image;
			Print("Saved %s! Used thread #%d of %d", frame->GetName().c_str(), omp_get_thread_num(), omp_get_max_threads());
		}
	}
}

