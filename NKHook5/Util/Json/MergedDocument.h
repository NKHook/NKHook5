#pragma once

#include <nlohmann/json.hpp>
#include <vector>

/*
* MergedDocument is a class to aid in the process of merging Json documents together.
* 
* Each document thats needs to be merged is given to the MergedDocument, which then automatically applies the
* json objects together. Whichever is applied last is the "top most". If there is a conflict in that a property
* already exists, it will be overridden by the newest applied document.
* 
* {
*	"propA": 100
* }
* 
* {
*	"propB": 200
* }
* 
* {
*	"propA": 300
* }
* 
* When these 3 are merged together, the expected result would be
* 
* {
*	"propA": 300,
*	"propB": 200
* }
*/

namespace NKHook5 {
	namespace Util {
		namespace Json {
			class MergedDocument {
				std::vector<nlohmann::json> documentsToMerge;
				nlohmann::json mergedDocument;
			public:
				MergedDocument();
				void Add(nlohmann::json);
				const nlohmann::json& GetMerged();
			};
		}
	}
}