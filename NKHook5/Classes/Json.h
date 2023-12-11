#pragma once

#include "../Util/NewFramework.h"
#include <json_spirit/json_spirit.h>

using JsonConfig = json_spirit::Config_vector<nfw::string>;
using JsonValue = json_spirit::Value_impl<JsonConfig>;