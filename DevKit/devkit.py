import sys
import argparse
import json
import shutil
from pathlib import Path
from zipfile import ZipFile

def CheckGameDir(gameDir):
	if gameDir == "":
		return False
	gamePath = Path(gameDir);
	if gamePath.is_dir():
		if (gamePath / "BTD5-Win.exe").is_file():
			return True
		elif (gamePath / "BTD5-Kong.exe").is_file():
			return True
		else:
			print("Couldn't find BTD5-Win.exe or BTD5-Kong.exe")
	else:
		print(gameDir + " is not a valid directory")
		return False
	return False

settings = {}
def ReadConf():
	global settings
	mdkConf = Path("mdkconf.json")
	if not mdkConf.exists():
		settins = {}
		return
	with open("mdkconf.json", 'r') as conf:
		settings = json.load(conf)

def SaveConf():
	global settings
	with open("mdkconf.json", 'w') as conf:
		json.dump(settings, conf)

def Setup():
	global settings
	gameDir = "";
	while not CheckGameDir(gameDir):
		gameDir = input("Where is Bloons TD 5 installed? >")

	settings["gameDir"] = gameDir
	SaveConf()

def DumpAssets():
	global settings
	print("(Step 1/2) Dumping game into './BTD5/'...")
	shutil.copytree(settings["gameDir"], "./BTD5/")

	print("(Step 2/2) Extracting BTD5.jet into Assets directory...")
	try:
		with ZipFile('./BTD5/Assets/BTD5.jet') as zf:
			zf.extractall(path="./BTD5/", pwd=b'Q%_{6#Px]]')
	except Exception as ex:
		print(ex)

	print("Asset dump complete!")

def CreateMod(modName):
	global settings
	try:
		baseAssets = Path("./BTD5/Assets/")
		if not baseAssets.exists():
			print("Please dump the game assets before creating a mod!")
			return False;

		modData = {}
		modData["name"] = modName
		modData["description"] = "A super awesome mod that adds 69 new towers and bloons"
		modData["version"] = "1.0.0"
		modData["authors"] = ["DisabledMallis", "EnabledMallis"]
		modData["website"] = "https://nkhook.github.io/"
		modData["github"] = "https://github.com/NKHook/NKHook5"

		modDir = Path(modName)
		if not modDir.exists():
			modDir.mkdir()

		vanillaDir = modDir / "Vanilla"
		if not vanillaDir.exists():
			shutil.copytree(baseAssets.resolve(), vanillaDir.resolve())

		modAssets = modDir / "Mod"
		if not modAssets.exists():
			modAssets.mkdir()

		modConf = modDir / "modinfo.json"
		with modConf.open(mode='w') as f:
			f.write(json.dumps(modData, indent=4))

		print("Your mod has been created! Happy modding!")
		return True
	except Exception as ex:
		print(ex)

	return False

parser = argparse.ArgumentParser("NKHook5 MDK")
parser.add_argument("--setup", help="Setup your MDK", required=False, action='store_true')
parser.add_argument("--dump-assets", help="Dump BTD5 assets", required=False, action='store_true')
parser.add_argument("--create-mod", help="Dump BTD5 assets", required=False)
args = parser.parse_args()
print(args)
ReadConf()

if args.setup:
	Setup()
if args.dump_assets:
	DumpAssets()
if not args.create_mod == None:
	CreateMod(args.create_mod)