#include "ReflectedDocument.h"

#include "../../Logging/Logger.h"

#include <deque>
#include <vector>

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
	char* allocated_filter = filter_doc->allocate_string(
		filter.c_str(),
		filter.size()+1
	);
	allocated_filter[filter.size()] = 0;
	filter_doc->parse<0>(
		allocated_filter
	);
	this->reflect_document = filter_doc;
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
				opParam = opParam->next_attribute();
			}

			//"with" requires a corresponding match
			if (match.empty() && !with.empty() || !match.empty() && with.empty()) {
				Print("\"match\" requires a corresponding \"with\" and vice-versa");
				continue;
			}

			rapidxml::xml_node<>* victimNode = nullptr;
			if (current_selection != nullptr)
				victimNode = current_selection->first_node();
			else
				victimNode = victim->first_node();
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

				//Check if deleted
				if (victimNode == nullptr || victimNode->parent() == nullptr) {
					break;
				}
				victimNode = victimNode->next_sibling();
			}
#pragma endregion
		}
		if (opName == "Delete") {
#pragma region delete_operation
			if (current_selection == nullptr) {
				Print("Please <Select/> before deleting an element!");
				continue;
			}
			if (victim == current_selection) {
				Print("Do not <Delete/> the entire document!");
				continue;
			}
			current_selection->parent()->remove_node(current_selection);
#pragma endregion
		}
		if (opName == "Insert") {
#pragma region insert_operation
			//Storage for parameters
			std::string node;
			std::vector<std::pair<std::string, std::string>> attribCopies;

			//Find the parameters from the attributes
			rapidxml::xml_attribute<>* opParam = curOp->first_attribute();
			//Check if the operation param even exists
			if (opParam == nullptr) {
				Print(LogLevel::ERR, "Insert operation must have 'node' as the first attribute");
				continue;
			}
			//First attribute must be the 'node' attribute, others are copied 1:1
			{
				std::string attribName(opParam->name());
				if (attribName == "node") {
					node = opParam->value();
					//Go to the next
					opParam = opParam->next_attribute();
				}
				else {
					Print(LogLevel::ERR, "Insert operation must have 'node' as the first attribute, not '%s'", opParam->name());
					continue;
				}
			}
			while (opParam) {
				//Store copies of each attribute
				std::string attribName(opParam->name());
				std::string attribValue(opParam->value());

				attribCopies.push_back({ attribName, attribValue });

				opParam = opParam->next_attribute();
			}
			//Create a new node and add the attributes
			rapidxml::xml_node<>* new_node = victim->allocate_node(rapidxml::node_element, 
				victim->allocate_string(
					node.c_str()),
					victim->allocate_string(curOp->value()),
					node.size(),
					curOp->value_size()
			);
			for (const auto& [key, value] : attribCopies) {
				rapidxml::xml_attribute<>* new_attrib = victim->allocate_attribute(
					victim->allocate_string(key.c_str()),
					victim->allocate_string(value.c_str()),
					key.size(),
					value.size()
				);
				new_node->append_attribute(new_attrib);
			}
			//Run ops on the new node
			ExecuteReflect(curOp, victim, new_node);
			//Append the new node
			current_selection->append_node(new_node);
#pragma endregion
		}
		if (opName == "Replace") {
#pragma region replace_operation
			//Storage for parameters
			std::string match;
			std::string with;

			//Find the parameters from the attributes
			rapidxml::xml_attribute<>* opParam = curOp->first_attribute();
			while (opParam) {
				std::string paramName(opParam->name());

				if (paramName == "match") {
					match = opParam->value();
				}
				if (paramName == "with") {
					with = opParam->value();
				}

				opParam = opParam->next_attribute();
			}

			//"with" requires a corresponding match
			if (match.empty() && !with.empty() || !match.empty() && with.empty()) {
				Print("\"match\" requires a corresponding \"with\" and vice-versa");
				continue;
			}

			rapidxml::xml_attribute<>* victimAttrib = current_selection->first_attribute();
			while (victimAttrib) {
				std::string attribName(victimAttrib->name());
				std::string attribValue(victimAttrib->value());

				if (attribName == match) {
					current_selection->remove_attribute(victimAttrib);
					rapidxml::xml_attribute<>* new_attrib = victim->allocate_attribute(
						victim->allocate_string(attribName.c_str()),
						victim->allocate_string(with.c_str()),
						attribName.size(),
						with.size()
					);
					current_selection->append_attribute(new_attrib);
				}

				victimAttrib = victimAttrib->next_attribute();
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
