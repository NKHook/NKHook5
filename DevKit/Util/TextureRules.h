#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

namespace DevKit {
	namespace Util {
		class CompileResult {
			std::string quality;
			std::string texture;
			std::string infoXml;
		public:
			CompileResult(std::string quality, std::string texture, std::string infoXml);
			CompileResult(nlohmann::json document);

			const std::string& GetQuality() const;
			const std::string& GetTexture() const;
			const std::string& GetInfoXml() const;
		};

		class Compile {
			std::string sourceDir;
			std::vector<CompileResult> results;
		public:
			Compile(std::string sourceDir, std::vector<CompileResult> results);
			Compile(nlohmann::json document);

			const std::string& GetSourceDir() const;
			const std::vector<CompileResult>& GetResults() const;
		};

		class TextureRules {
			std::vector<std::string> reflections;
			std::vector<Compile> compiles;
		public:
			TextureRules(std::vector<std::string> reflections, std::vector<Compile> compiles);
			TextureRules(nlohmann::json document);

			const std::vector<std::string>& GetReflects() const;
			const std::vector<Compile>& GetCompiles() const;
		};
	}
}