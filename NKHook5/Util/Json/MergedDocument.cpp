#include "MergedDocument.h"

using namespace NKHook5::Util::Json;

MergedDocument::MergedDocument()
{
}

nlohmann::ordered_json Merge(nlohmann::ordered_json base, nlohmann::ordered_json next) {
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
			if (result[i].is_primitive() && next[i].is_primitive()) {
				result[i] = next[i];
			}
			if (result[i].is_array() && next[i].is_array()) {
				result[i] = Merge(result[i], next[i]);
			}
			if (result[i].is_object() && next[i].is_object()) {
				result[i] = Merge(result[i], next[i]);
			}
			if (result[i].type() != next[i].type()) {
				result[i] = next[i];
			}
		}
	}
	if (result.is_object() && next.is_object()) {
		for (const auto& [key, value] : next.items()) {
			if (!result.contains(key)) {
				result[key] = value;
				continue;
			}

			//If it does have the key
			result[key] = Merge(result[key], value);
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

	this->mergedDocument = Merge(this->mergedDocument, toMerge);
}

const nlohmann::ordered_json& MergedDocument::GetMerged()
{
	return this->mergedDocument;
}
