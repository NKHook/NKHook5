#include "MergedDocument.h"

using namespace NKHook5::Util::Json;

MergedDocument::MergedDocument()
{
}

void MergedDocument::Add(nlohmann::json toMerge)
{
	this->documentsToMerge.push_back(toMerge);

	this->mergedDocument.update(toMerge);
}

const nlohmann::json& MergedDocument::GetMerged()
{
	return this->mergedDocument;
}
