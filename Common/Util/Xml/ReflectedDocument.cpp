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

void ReflectedDocument::Reflect(rapidxml::xml_document<>* victim)
{
	//Find our reflection node
	rapidxml::xml_node<>* reflectNode = this->reflect_document->first_node();
	while (reflectNode) {
		std::string reflectNodeName(reflectNode->name());
		//Once found, we can start reflection work
		if (reflectNodeName == "Reflect") {
			//A place to store the results from selects
			std::deque<rapidxml::xml_node<>*> selects;
			//Iterate the child nodes of operations
			rapidxml::xml_node<>* curOp = reflectNode->first_node();
			while (curOp) {
				//Get the operation name
				std::string opName(curOp->name());
				//If select operation
				if (opName == "Select") {
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
						if (victimNodeName == node) {
							selects.push_back(victimNode);
						}

						victimNode = victimNode->next_sibling();
					}
				}

				curOp = curOp->next_sibling();
			}

			//Return once we're done
			break;
		}
	}
}
