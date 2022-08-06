#include "Feature.h"

using namespace DevKit;
using namespace DevKit::Features;

Feature::Feature(std::string name, std::string helpDesc) {
	this->name = name;
	this->helpDesc = helpDesc;
}

const std::string& Feature::GetName() {
	return this->name;
}

std::string Feature::ActivatorArgs()
{
	return "";
}

std::string& Feature::HelpDesc()
{
	return this->helpDesc;
}

void Feature::Run() {

}