#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <optional>

namespace Common {
	namespace Mod {
		enum class LoadOrder {
			BASE,
			FIRST,
			ANY,
			LAST
		};

		class ModInfo {
			std::string name;
			std::string description;
			std::string version;
			std::vector<std::string> authors;
			std::string website;
			std::string discord;
			std::string github;
			std::optional<LoadOrder> loadOrder;
			std::vector<std::string> incompatibilites;
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
			const std::optional<LoadOrder> GetLoadOrder() const;
			const std::optional<std::vector<std::string>> GetIncompatibilites() const;

			void SetName(std::string);
			void SetDescription(std::string);
			void SetVersion(std::string);
			void SetAuthors(std::vector<std::string>);
			void SetWebsite(std::string);
			void SetDiscord(std::string);
			void SetGithub(std::string);
			void SetLoadOrder(LoadOrder);
			void SetIncompatibilities(std::vector<std::string>);
		};
	}
}