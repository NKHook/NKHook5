#pragma once

#include <nlohmann/json.hpp>
#include <vector>

/*
* StrippedDocument is a class to aid in the process of stripping Json documents apart.
*
* Its effectively the opposite of MergedDocument. Instead of mashing two documents together, this
* aims to remove any matching keys.
*
* {
*	"propA": 100,
*	"propB": 200,
*	"propC": 300,
*	"propD": 400
* }
*
* {
*	"propA": 300,
*	"propB": 200,
*	"propC": 100
* }
*
* When these 2 are merged together, the expected result would be
*
* {
*	"propA": 300,
*	"propC": 100
* }
*/

namespace Common {
	namespace Util {
		namespace Json {
			class StrippedDocument {
				std::vector<nlohmann::ordered_json> documentsToStrip;
				nlohmann::ordered_json strippedDocument;
			public:
				StrippedDocument();
				void Add(nlohmann::ordered_json);
				const nlohmann::ordered_json& GetStripped();
			};
		}
	}
}