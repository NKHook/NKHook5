#include "SpriteExtract.h"
#include "../Files/PngPhoto.h"
#include "../Files/JPngPhoto.h"
#include "../Logging/Logger.h"
#include "../Sprites/Images/MTImage.h"
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
	auto& xmls = table->GetXmls();
	fs::path resultDir = this->resultDir;
	for (auto* xmlInfo : xmls) {
		TexType type = xmlInfo->GetTexType();
		if (type != TexType::PNG && type != TexType::JPNG) {
			Print(LogLevel::WARNING, "Skipping XML with a texType that is not PNG or JPNG");
			return;
		}

		std::string xmlName = xmlInfo->GetName();
		fs::path xmlOutDir = resultDir / xmlName;

		auto& frames = xmlInfo->GetFrames();
		for (auto* frame : frames) {
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
			}

			Print("Saved %s!", frame->GetName().c_str());
		}
	}
}

