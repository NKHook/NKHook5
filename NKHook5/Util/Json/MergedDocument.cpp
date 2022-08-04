#include "MergedDocument.h"

using namespace NKHook5::Util::Json;

MergedDocument::MergedDocument()
{
}

nlohmann::ordered_json Merge(nlohmann::ordered_json base, nlohmann::ordered_json next, MergeMode mode) {
	nlohmann::json result = base;
	if (next.is_null()) {
		if (result.is_null()) {
			printf("Please don't merge null documents!");
#ifdef _DEBUG
			throw std::exception("Attempted to merge 2 null documents");
#endif
		}
		return base;
	}
	if (result.is_null()) {
		return next;
	}
	if (result.type() != next.type()) {
		printf("Please don't try to merge documents of differing types!");
#ifdef _DEBUG
		throw std::exception("Attempted to merge documents of differing types");
#endif
	}
	if (result.is_array() && next.is_array()) {
		for (int i = 0; i < next.size(); i++) {
			
			if (next[i].is_null()) {
				continue;
			}
			//Behavior on insertive mode only
			if (mode == MergeMode::INSERTIVE) {
				result.push_back(next[i]);
				continue;
			}

			//Every other mode uses this logic
			if (result.size() <= i) {
				result.push_back(next[i]);
			}
			if (result[i].is_primitive() && next[i].is_primitive()) {
				result[i] = next[i];
			}
			if (result[i].is_array() && next[i].is_array()) {
				result[i] = Merge(result[i], next[i], mode);
			}
			if (result[i].is_object() && next[i].is_object()) {
				result[i] = Merge(result[i], next[i], mode);
			}
			if (result[i].type() != next[i].type()) {
				result[i] = next[i];
			}
		}
	}
	if (result.is_object() && next.is_object()) {
		if (next.contains("MERGE_MODE")) {
			if (next["MERGE_MODE"] == "INSERTIVE") {
				mode = MergeMode::INSERTIVE;
			}
			if (next["MERGE_MODE"] == "SUBSTITUTIVE") {
				mode = MergeMode::SUBSTITUTIVE;
			}
		}
		for (const auto& [key, value] : next.items()) {
			if (!result.contains(key)) {
				result[key] = value;
				continue;
			}

			//If it does have the key
			result[key] = Merge(result[key], value, mode);
		}
	}
	if (result.is_primitive() && next.is_primitive()) {
		result = next;
	}

	return result;
}

void MergedDocument::Add(nlohmann::ordered_json toMerge)
{
	if (toMerge.is_null()) {
		return;
	}

	this->documentsToMerge.push_back(toMerge);

	MergeMode mode = MergeMode::SUBSTITUTIVE;
	if (toMerge.contains("MERGE_MODE")) {
		if (toMerge["MERGE_MODE"] == "INSERTIVE") {
			mode = MergeMode::INSERTIVE;
		}
		if (toMerge["MERGE_MODE"] == "SUBSTITUTIVE") {
			mode = MergeMode::SUBSTITUTIVE;
		}
	}

	this->mergedDocument = Merge(this->mergedDocument, toMerge, mode);
}

void MergedDocument::Add(nlohmann::ordered_json toMerge, MergeMode mode)
{
	if (toMerge.is_null()) {
		return;
	}

	this->documentsToMerge.push_back(toMerge);

	this->mergedDocument = Merge(this->mergedDocument, toMerge, mode);
}

const nlohmann::ordered_json& MergedDocument::GetMerged()
{
	return this->mergedDocument;
}
