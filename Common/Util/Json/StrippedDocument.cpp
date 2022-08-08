#include "StrippedDocument.h"
#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Util;
using namespace Common::Util::Json;

StrippedDocument::StrippedDocument()
{
}

nlohmann::ordered_json Strip(nlohmann::ordered_json base, nlohmann::ordered_json next) {
	nlohmann::ordered_json result = next;
	bool needsInsertive = false;

	if (next.is_null()) {
		if (result.is_null()) {
			Logger::Print(Logger::LogLevel::ERR, "Please don't strip null documents!");
			throw std::exception("Attempted to strip a pair of null documents");
		}
		return result;
	}
	if (result.is_null()) {
		return next;
	}
	if (result.type() != next.type()) {
		Logger::Print(Logger::LogLevel::ERR, "Please don't try to strip documents of differing types!");
		throw std::exception("Attempted to strip documents of differing types");
	}
	if (base == result) {
		return nlohmann::ordered_json();
	}
	if (base.is_array()) {
		size_t len = std::max(base.size(), next.size());
		for (size_t i = 0; i < len; i++) {
			if (base[i].is_null()) {
				continue;
			}
			nlohmann::ordered_json baseValue = base[i];
			if (next[i].is_null()) {
				continue;
			}
			nlohmann::ordered_json nextValue = next[i];
			if (baseValue.type() != nextValue.type()) {
				Logger::Print(Logger::LogLevel::ERR, "Please don't try to strip lists of differing types!");
				throw std::exception("Attempted to strip documents of differing types");
			}
			if (baseValue.is_object() || baseValue.is_array()) {
				result[i] = Strip(baseValue, nextValue);
				continue;
			}
			if (baseValue == nextValue) {
				result[i] = nlohmann::ordered_json();
				continue;
			}
		}
	}
	if (base.is_object()) {
		for (const auto& [key, value] : base.items()) {
			if (result.contains(key)) {
				if (result[key] == value) {
					result.erase(key);
					continue;
				}
				if (result[key].type() != value.type())
					continue;
				if ((result[key].is_object() && value.is_object()) || (result[key].is_array() && value.is_array())) {
					result[key] = Strip(value, result[key]);
					if (needsInsertive && !result.contains("MERGE_MODE")) {
						result["MERGE_MODE"] = "INSERTIVE";
					}
				}
			}
		}
	}
	return result;
}

void StrippedDocument::Add(nlohmann::ordered_json toStrip)
{
	if (toStrip.is_null()) {
		return;
	}

	this->documentsToStrip.push_back(toStrip);

	this->strippedDocument = Strip(this->strippedDocument, toStrip);
}

const nlohmann::ordered_json& StrippedDocument::GetStripped()
{
	return this->strippedDocument;
}
