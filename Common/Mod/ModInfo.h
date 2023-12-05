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
			explicit ModInfo(nlohmann::json);
			void Initialize(nlohmann::json);
			nlohmann::json Serialize();

			[[nodiscard]] const std::string& GetName() const;
			[[nodiscard]] const std::string& GetDescription() const;
			[[nodiscard]] const std::string& GetVersion() const;
			[[nodiscard]] const std::vector<std::string>& GetAuthors() const;
			[[nodiscard]] const std::string& GetWebsite() const;
			[[nodiscard]] const std::string& GetDiscord() const;
			[[nodiscard]] const std::string& GetGithub() const;
			[[nodiscard]] const std::optional<LoadOrder> GetLoadOrder() const;
			[[nodiscard]] const std::optional<std::vector<std::string>> GetIncompatibilites() const;

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