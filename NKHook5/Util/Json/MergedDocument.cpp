#include "MergedDocument.h"

using namespace NKHook5::Util::Json;

MergedDocument::MergedDocument()
{
}

void MergedDocument::Add(nlohmann::json toMerge)
{
	this->documentsToMerge.push_back(toMerge);

	if (this->mergedDocument.is_null()) {
		this->mergedDocument = toMerge;
	}

	if(toMerge.is_object() && this->mergedDocument.is_object())
		this->mergedDocument.update(toMerge);

	if (toMerge.is_array() && this->mergedDocument.is_array()) {
		for (const auto& elem : toMerge) {
			if (!this->mergedDocument.contains(elem)) {
				this->mergedDocument.push_back(elem);
			}
		}
	}
}

const nlohmann::json& MergedDocument::GetMerged()
{
	return this->mergedDocument;
}
