#include "TextureStep.h"

#include "../Util/TextureRules.h"

#include <Files/File.h>
#include <Files/PngPhoto.h>
#include <Sprites/Documents/XmlInfo.h>
#include <Sprites/Images/CLImage.h>

#include <binpack2d.hpp>
#include <rapidxml.hpp>
#include <rapidxml_ext.hpp>
#include <rapidxml_print.hpp>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Mod;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;
using namespace Common::Sprites::Images;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;
using namespace DevKit::Util;
namespace fs = std::filesystem;

TextureStep::TextureStep() : PackageStep("Textures")
{
}

bool TextureStep::Execute(Project& proj, ZipBase& arch)
{
	fs::path modTextures = proj.GetModPath() / "Textures";
	fs::path vanillaTextures = proj.GetVanillaPath() / "Textures";

	fs::path texRules = modTextures / "Rules.json";
	File rulesFile;
	rulesFile.OpenRead(texRules);
	std::string rulesJson = rulesFile.ReadStr();
	rulesFile.Close();

	nlohmann::json parsedRules = nlohmann::json::parse(rulesJson);
	TextureRules rules(parsedRules);
	const std::vector<Compile>& texCompiles = rules.GetCompiles();
	for (const Compile& compile : texCompiles) {
		fs::path sourceDir = modTextures / compile.GetSourceDir();

		//We need to calculate the size the atlas needs to be
		BinPack2D::CanvasArray<
			std::pair<std::string, Image*>
		> atlasArray = BinPack2D::UniformCanvasArrayBuilder<
			std::pair<std::string, Image*>
		>(0x1000, 0x1000, 1).Build();

		BinPack2D::ContentAccumulator<std::pair<std::string, Image*>> inputContent;
		for (const auto& dirEntry : fs::directory_iterator(sourceDir)) {
			fs::path entryPath = dirEntry;
			//If the entry is a directory, its an animation
			if (dirEntry.is_directory()) {

			}
			//Else its just a sprite
			else {
				std::string imageName = entryPath.stem().string();
				PngPhoto spriteFile;
				spriteFile.OpenRead(dirEntry);
				Image* spriteImage = spriteFile.ReadImg();
				inputContent += BinPack2D::Content<std::pair<std::string, Image*>>(
					{
						imageName,
						spriteImage
					},
					BinPack2D::Coord(),
					BinPack2D::Size(
						spriteImage->GetWidth(),
						spriteImage->GetHeight()
					),
					false);
				spriteFile.Close();
			}
		}
		//Sort the images by size for efficient packing
		inputContent.Sort();
		//Place the content into the canvas
		atlasArray.Place(inputContent);
		//Get the output content
		BinPack2D::ContentAccumulator<std::pair<std::string, Image*>> outputContent;
		atlasArray.CollectContent(outputContent);
		//Find the width and height after sort
		size_t furthestX = 0;
		size_t furthestY = 0;
		for (const auto& content : outputContent.Get()) {
			size_t posX = content.coord.x;
			size_t posY = content.coord.y;
			size_t width = content.size.w;
			size_t height = content.size.h;

			size_t farX = posX + width;
			size_t farY = posY + height;

			if (furthestX < farX) {
				furthestX = farX;
			}

			if (furthestY < farY) {
				furthestY = farY;
			}
		}
		//Image for main texture atlas
		//Create array of empty color data
		std::vector<uint32_t> colorData(furthestX * furthestY);
		//Create image with empty color data with size
		CLImage atlas(colorData, furthestX, furthestY);

		//Iterate the content again and draw the images at locations
		for (const auto& content : outputContent.Get()) {
			//Get the size from calculations
			size_t posX = content.coord.x;
			size_t posY = content.coord.y;
			size_t width = content.size.w;
			size_t height = content.size.h;

			//Get the texture image
			CLImage* texImage = (CLImage*)content.content.second;
			//Paste it in the atlas
			atlas.PasteImage(texImage, posX, posY, width, height);
		}

		//Export the atlas to an image file
		for (const CompileResult& result : compile.GetResults()) {
			std::string quality = result.GetQuality();
			std::string texFile = result.GetTexture();
			std::string infoXml = result.GetInfoXml();

			fs::path resultFile = modTextures / quality / texFile;
			fs::create_directories(resultFile.parent_path());
			PngPhoto resultPhoto;
			resultPhoto.OpenWrite(resultFile);
			resultPhoto.WriteImg(&atlas);
			resultPhoto.Close();
		}

		//Export the atlas' XML map
		for (const CompileResult& result : compile.GetResults()) {
			std::string quality = result.GetQuality();
			std::string texFile = result.GetTexture();
			std::string infoXml = result.GetInfoXml();

			fs::path resultPath = modTextures / quality / infoXml;
			fs::create_directories(resultPath.parent_path());

			XmlInfo* spriteInfo = XmlInfo::Create(compile.GetSourceDir(), TexType::PNG);
			FrameInfo* frameInfo = FrameInfo::Create(
				compile.GetSourceDir(),
				TexType::PNG,
				furthestX,
				furthestY
			);
			spriteInfo->AddFrame(frameInfo);
			//Iterate the content again and store the image locations in XML
			for (const auto& content : outputContent.Get()) {
				//Get the size from calculations
				size_t posX = content.coord.x;
				size_t posY = content.coord.y;
				size_t width = content.size.w;
				size_t height = content.size.h;

				Cell* imageCell = Cell::Create(
					content.content.first,
					posX,
					posY,
					width,
					height,
					0,
					0,
					width,
					height
				);

				frameInfo->AddCell(imageCell);
			}

			std::string xmlStr;
			rapidxml::xml_document<>* spriteSheet = spriteInfo->ToXML();
			rapidxml::internal::print_node(std::back_inserter(xmlStr), spriteSheet, 0, 0);

			File resultFile;
			resultFile.OpenWrite(resultPath);
			resultFile.WriteStr(xmlStr);
			resultFile.Close();

			delete spriteInfo;
		}

		//Free the images
		for (const auto& content : inputContent.Get()) {
			delete content.content.second;
		}
	}

	return true;
}
