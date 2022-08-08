#include "Package.h"
#include <iostream>
#include <algorithm>

using namespace DevKit;
using namespace DevKit::Features;

Package::Package() : Feature("package", "Packages a mod into a given mod format")
{
}

std::string Package::ActivatorArgs()
{
	return "-p, --package";
}

int Package::MaxArgs()
{
	return 3;
}

void Package::Run(std::vector<std::string> args)
{
	std::string modName = args[0];
	ModFmt modFmt = ModFmt::NONE;
	if (args.size() > 1) {
		std::transform(args[1].begin(), args[1].end(), args[1].begin(), [](unsigned char c) { return std::tolower(c); });
		if (args[1] == "nkh") {
			modFmt = ModFmt::NKH;
		}
		else if (args[1] == "assetbundles") {
			modFmt = ModFmt::ASSETBUNDLES;
		}
		else if (args[1] == "jet") {
			modFmt = ModFmt::JET;
		}
		else if (args[1] == "unpacked") {
			modFmt = ModFmt::UNPACKED;
		}
		else {
			modFmt = ModFmt::NONE;
		}
	}
	if (modFmt == ModFmt::NONE) {
		printf("When packaging a mod, you must choose a format.\n");
		printf("The NKHook5 DevKit supports many formats for mods. Each have their own pros and cons.\n");
		printf("NOTE: Some formats require the vanilla assets to be packaged with them. To avoid copyright infringement, its wise to not distribute mods with these formats.\n");
		printf("\n");
		printf("1. nkh\n");
		printf("\tFormat made for mods that use NKHook5 and its features\n");
		printf("\tPros:\n");
		printf("\t- Small file size (easy to distribute)\n");
		printf("\t- No vanilla assets required\n");
		printf("\t- Can take full advantage of NKHook5's features\n");
		printf("\t- Allows your mod to work with other mods by default\n");
		printf("\tCons:\n");
		printf("\t- Requires NKHook5 to use\n");
		printf("\t- May be a little slower on older machines (due to extreme compression)\n");
		printf("2. AssetBundles\n");
		printf("\tA format made by Ninja Kiwi to allow them to update certain parts of their games to save on resources\n");
		printf("\tPros:\n");
		printf("\t- Does not require NKHook5\n");
		printf("\t- No vanilla assets required\n");
		printf("\t- Can allow your mod to work with other mods\n");
		printf("\tCons:\n");
		printf("\t- May not be able to make use of NKHook5's features\n");
		printf("\t- Proprietary\n");
		printf("3. jet\n");
		printf("\tA format made by Ninja Kiwi for protecting assets from being tampered (how naive)\n");
		printf("\tPros:\n");
		printf("\t- Most popular format for mods before AssetBundles was used\n");
		printf("\tCons:\n");
		printf("\t- Requires vanilla assets\n");
		printf("\t- Requires user to replace files to use\n");
		printf("4. Unpacked archive\n");
		printf("\tNot really a format for mod use, but can be used to share mod source code\n");
		printf("\tPros:\n");
		printf("\t- Git not required for mod collaboration\n");
		printf("\tCons:\n");
		printf("\t- Only one person can edit a file in the mod at a time to avoid conflict\n");
		printf("\t- Very hard to install as a mod\n");
		printf("\t- Large file size\n");
		printf("\t- Includes vanilla assets\n");
		int choice = 0;
#define CHECK_CHOICE(v) (v > 0 && v < 5)
		do {
			if (CHECK_CHOICE(choice))
				break;
			printf("\nWhich format would you like to use? (1-4): ");
			if (!(std::cin >> choice)) {
				printf("Error, please try again.");
				std::cin.clear();
				std::cin.ignore();
			}
		} while (true);
		modFmt = (ModFmt)choice;
	}

	if (modFmt == ModFmt::NONE) {
		printf("Please specify a valid mod format!");
		return;
	}


}