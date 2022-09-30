#include "SpriteExtract.h"
#include "../Files/PngPhoto.h"
#include "../Logging/Logger.h"
#include "../Sprites/Images/CLImage.h"
#include "../Threading/WorkerThread.h"
#include "../Threading/WorkGroup.h"

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
	WorkGroup extractWorkers(16);

	auto& xmls = table->GetXmls();
	for (auto* xmlInfo : xmls) {
		TexType type = xmlInfo->GetTexType();
		if (type != TexType::PNG) {
			Print(LogLevel::WARNING, "Skipping XML with a texType that is not PNG");
			continue;
		}

		std::string xmlName = xmlInfo->GetName();
		fs::path xmlOutDir = resultDir / xmlName;

		auto& frames = xmlInfo->GetFrames();
		for (auto* frame : frames) {
			fs::path imagePath = frame->GetImagePath();
			PngPhoto imageFile;
			imageFile.OpenRead(imagePath);
			CLImage* image = (CLImage*)imageFile.ReadImg();

			for (auto* anim : frame->GetAnimations()) {
				fs::path animOutDir = xmlOutDir / anim->GetName();

				for (auto* cell : anim->GetCells()) {
					fs::path cellFilePath = animOutDir / std::string(cell->GetName() + ".png");
					//Make necessary parent dirs
					fs::create_directories(cellFilePath.parent_path());

					extractWorkers.DoWork([&]() {
						CLImage* splitImage = image->CopyImage(cell->GetX(), cell->GetY(), cell->GetWidth(), cell->GetHeight());
						PngPhoto cellPhoto;
						cellPhoto.OpenWrite(cellFilePath);
						cellPhoto.WriteImg(splitImage);
						cellPhoto.Close();

						delete splitImage;
					});
				}
			}
			for (auto* cell : frame->GetCells()) {
				fs::path cellFilePath = xmlOutDir / std::string(cell->GetName() + ".png");
				//Make necessary parent dirs
				fs::create_directories(cellFilePath.parent_path());

				extractWorkers.DoWork([&]() {
					CLImage* splitImage = image->CopyImage(cell->GetX(), cell->GetY(), cell->GetWidth(), cell->GetHeight());
					PngPhoto cellPhoto;
					cellPhoto.OpenWrite(cellFilePath);
					cellPhoto.WriteImg(splitImage);
					cellPhoto.Close();

					delete splitImage;
				});
			}

			Print("Extraction complete, waiting for extract worker to finish...");
			extractWorkers.AwaitQueue();
			Print("Saved %s!", frame->GetName().c_str());

			delete image;
		}
	}

}

