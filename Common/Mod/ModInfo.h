#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

namespace Common {
	namespace Mod {
		class ModInfo {
			std::string name;
			std::string description;
			std::string version;
			std::vector<std::string> authors;
			std::string website;
			std::string discord;
			std::string github;
		public:
			ModInfo();
			ModInfo(nlohmann::json);
			void Initialize(nlohmann::json);
			nlohmann::json Serialize();

			const std::string& GetName() const;
			const std::string& GetDescription() const;
			const std::string& GetVersion() const;
			const std::vector<std::string>& GetAuthors() const;
			const std::string& GetWebsite() const;
			const std::string& GetDiscord() const;
			const std::string& GetGithub() const;

			void SetName(std::string);
			void SetDescription(std::string);
			void SetVersion(std::string);
			void SetAuthors(std::vector<std::string>);
			void SetWebsite(std::string);
			void SetDiscord(std::string);
			void SetGithub(std::string);
		};
	}
}