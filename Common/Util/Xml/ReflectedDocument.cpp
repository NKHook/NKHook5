#include "ReflectedDocument.h"

#include "../../Logging/Logger.h"

#include <deque>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;
using namespace Common::Util::Xml;

ReflectedDocument::ReflectedDocument()
{
}

ReflectedDocument::ReflectedDocument(std::string filter)
{
	rapidxml::xml_document<>* filter_doc = new rapidxml::xml_document<>();
	filter_doc->parse<0>((char*)filter.c_str());
}

ReflectedDocument::~ReflectedDocument()
{
	delete this->reflect_document;
}

//A function to do the reflection work recursively
void ExecuteReflect(rapidxml::xml_node<>* reflectNode, rapidxml::xml_document<>* victim, rapidxml::xml_node<>* current_selection) {
	//Iterate the child nodes of operations
	rapidxml::xml_node<>* curOp = reflectNode->first_node();
	while (curOp) {
		//Get the operation name
		std::string opName(curOp->name());
		//If select operation
		if (opName == "Select") {
#pragma region select_operation
			//Storage for parameters
			std::string node;
			std::string match;
			std::string with;

			//Find the parameters from the attributes
			rapidxml::xml_attribute<>* opParam = curOp->first_attribute();
			while (opParam) {
				std::string paramName(opParam->name());

				if (paramName == "node") {
					node = opParam->value();
				}
				if (paramName == "match") {
					match = opParam->value();
				}
				if (paramName == "with") {
					with = opParam->value();
				}
			}

			//"with" requires a corresponding match
			if (match.empty() && !with.empty() || !match.empty() && with.empty()) {
				Print("\"match\" requires a corresponding \"with\" and vice-versa");
				match = "";
				with = "";
			}

			rapidxml::xml_node<>* victimNode = victim->first_node();
			while (victimNode) {
				std::string victimNodeName(victimNode->name());

				bool matches = match.empty();
				if (!match.empty()) {
					rapidxml::xml_attribute<>* victimAttrib = victimNode->first_attribute();
					while (victimAttrib) {
						std::string attribName(victimAttrib->name());
						std::string attribValue(victimAttrib->value());

						if (attribName == match && attribValue == with) {
							matches = true;
						}

						victimAttrib = victimAttrib->next_attribute();
					}
				}

				if (victimNodeName == node && matches) {
					ExecuteReflect(curOp, victim, victimNode);
				}

				victimNode = victimNode->next_sibling();
			}
#pragma endregion
		}

		curOp = curOp->next_sibling();
	}
}

void ReflectedDocument::Reflect(rapidxml::xml_document<>* victim)
{
	//Find our reflection node
	rapidxml::xml_node<>* reflectNode = this->reflect_document->first_node();
	while (reflectNode) {
		std::string reflectNodeName(reflectNode->name());
		//Once found, we can start reflection work
		if (reflectNodeName == "Reflect") {
			ExecuteReflect(reflectNode, victim, nullptr);

			//Return once we're done
			break;
		}
	}
}
