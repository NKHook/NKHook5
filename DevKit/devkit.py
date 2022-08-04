import sys
import argparse
import json
import shutil
import os
import jsonutil
from nfpkg import *
from pathlib import Path
from zipfile import ZipFile

tempdir = Path("Temp")
dumpIgnore = [
	"*.exe",
	"*.dll",
	"*.jet",
	"api_key.txt",
	"AssetBunles/"
]

def CheckGameDir(gameDir):
	if gameDir == "":
		return None
	gamePath = Path(gameDir);
	if gamePath.is_dir():
		if (gamePath / "BTD5-Win.exe").is_file():
			return "BTD5-Win.exe"
		elif (gamePath / "BTD5-Kong.exe").is_file():
			return "BTD5-Kong.exe"
		else:
			print("Couldn't find BTD5-Win.exe or BTD5-Kong.exe")
	else:
		print(gameDir + " is not a valid directory")
		return None
	return None

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

def ReadModConf(modName):
	modConf = Path(modName) / "modinfo.json"
	if not modConf.exists():
		return {}
	with modConf.open() as conf:
		return json.load(conf)

def Setup():
	global settings
	gameDir = "";
	while CheckGameDir(gameDir) == None:
		gameDir = input("Where is Bloons TD 5 installed? >")

	settings["gameDir"] = gameDir
	settings["exeName"] = CheckGameDir(gameDir)
	SaveConf()

def DumpAssets():
	global settings
	print("(Step 1/3) Dumping game into './BTD5/'...")
	shutil.copytree(settings["gameDir"], "./BTD5/")

	print("(Step 2/3) Extracting BTD5.jet into Assets directory...")
	try:
		with ZipFile('./BTD5/Assets/BTD5.jet') as zf:
			zf.extractall(path="./BTD5/", pwd=b'Q%_{6#Px]]')
	except Exception as ex:
		print(ex)

	print("(Step 3/3) Clean up useless files from dump...")
	for root, dirs, files in os.walk("./BTD5/"):
		for name in files:
			filePath = Path(os.path.join(root, name))
			for ignore in dumpIgnore:
				if filePath.match(ignore):
					print("Removing '" + str(filePath) + "'...")
					os.remove(str(filePath))

	print("Asset dump complete!")

def CreateMod(modName):
	global settings
	print("Creating your mod...")
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

		UpdateMod(modName)

		modConf = modDir / "modinfo.json"
		with modConf.open(mode='w') as f:
			f.write(json.dumps(modData, indent=4))

		print("Your mod has been created! Happy modding!")
		return True
	except Exception as ex:
		print(ex)
		print("Mod creation failed!")

	return False

def OpenEditor(modName):
	os.system("code "+modName)

def RunMod(modName):
	global settings
	modDir = Path(modName)
	if not modDir.exists():
		print("No suck mod "+modName+" exists")
		return
	gameDir = Path(settings["gameDir"])
	loaderDll = gameDir / "wininet.dll"
	nkhDll = gameDir / "NKHook5.dll"
	if not loaderDll.exists():
		print("Cannot launch mod! wininet.dll is missing!")
	if not nkhDll.exists():
		print("Cannot launch mod! NKHook5.dll is missing!")

	btdExe = gameDir / settings["exeName"]
	launchCmd = str(btdExe.resolve())+" --LaunchMod "+str(modDir.resolve())
	print("Launching BTD5 with "+launchCmd)
	cwd = os.getcwd()
	os.chdir(gameDir)
	os.system(launchCmd)
	os.chdir(cwd)

def MakeGit(modName, remote):
	global settings
	modDir = Path(modName)
	if not modDir.exists():
		print("No such mod "+modName+" exists")
		return
	modSettings = ReadModConf(modName)
	if modSettings == {}:
		print("Could not read modinfo for "+modName)
	if shutil.which("git") is None:
		print("Git is not installed!")
		return
	cwd = os.getcwd()
	os.chdir(modDir)
	os.system("git init")
	if not remote == None:
		os.system("git remote add origin "+remote)

	defaultIgnore = """
Vanilla/
"""
	with open(".gitignore", "w") as f:
		f.write(defaultIgnore)

	readme = Path("readme.md")
	if not readme.exists():
		with readme.open("w") as f:
			defaultReadme = "# " + modName + """
""" + modSettings["description"] + """

Made with the NKHook5 Mod Development Kit
"""
			f.write(defaultReadme)

	shouldCommit = input("Would you like to push the mod code to the remote? (Y/N)")
	if shouldCommit.lower() == "y":
		os.system("git add .")
		os.system("git commit -m \"Created Git repository for "+modName+"\"")
		os.system("git push origin master")

	os.chdir(cwd)

def CloneMod(modUrl):
	if shutil.which("git") is None:
		print("Git is not installed!")
		return
	os.system("git clone "+modUrl)

def UpdateMod(modName):
	global settings
	
	modDir = Path(modName)
	baseAssets = Path("./BTD5/Assets/")
	if not baseAssets.exists():
		print("Please dump the game assets before creating/updating a mod!")
		return False;

	print("Updating Vanilla assets...")
	vanillaDir = modDir / "Vanilla"
	if vanillaDir.exists():
		shutil.rmtree(vanillaDir.resolve())
	shutil.copytree(baseAssets.resolve(), vanillaDir.resolve())
	print("Vanilla assets updated!")

	modAssets = modDir / "Mod"
	if not modAssets.exists():
		modAssets.mkdir()

def WalkAssets(modDir, modAssets):
	assetFiles = []
	pathsOnDisk = []
	for root, dirs, files in os.walk(modDir):
		for name in files:
			if str(modAssets) in root:
				nameInPkg = os.path.join(root, name).replace(str(modAssets), "Assets")
				assetFiles.append(nameInPkg)
				pathsOnDisk.append(os.path.join(root, name))
	return zip(assetFiles, pathsOnDisk)

def PackageUnpacked(modDir, modSettings, modFile, type):
	modAssets = modDir / "Mod"
	modPkg = Package(modFile, packageType=type)
	for nameInPkg, nameOnDisk in WalkAssets(modDir, modAssets):
		if str(modAssets) in root:
			print("Packing '"+nameInPkg+"'...")
			modPkg.Write(nameInPkg, nameOnDisk)
	return modPkg

def PackageJet(modDir, modSettings, modFile, type, includeVanilla=True):
	vanillaAssets = modDir / "Vanilla"
	modAssets = modDir / "Mod"
	modPkg = Package(modFile, packageType=type)

	print("Loading mod assets...")
	for nameInPkg, nameOnDisk in WalkAssets(modDir, modAssets):
		vanillaPath = nameOnDisk.replace("Mod", "Vanilla")
		if os.path.exists(vanillaPath):
			try:
				print("JSON DOCUMENT MERGE RESULT")
				vanJson = None 
				with open(vanillaPath, 'r') as vf:
					vanJson = json.load(vf)

				print("BASE DOCUMENT")
				print(json.dumps(vanJson, indent=4))
				print("END BASE DOCUMENT")

				modJson = None
				with open(nameOnDisk, 'r') as mf:
					modJson = json.load(mf)

				print("NEXT DOCUMENT")
				print(json.dumps(modJson, indent=4))
				print("END NEXT DOCUMENT")

				mergedJson = jsonutil.merge(vanJson, modJson)
				
				print("BEGIN RESULT")
				print(json.dumps(mergedJson, indent=4))
				print("END RESULT")
				print("END OF MERGE RESULT")
				
				print("Loading '"+str(nameInPkg)+"' from '"+str(nameOnDisk)+"' merged with '"+str(vanillaPath)+"'...")
				mergeTemp = tempdir / nameInPkg
				mergeTemp.parents[0].mkdir(parents=True, exist_ok=True)
				with open(mergeTemp, 'w') as f:
					json.dump(mergedJson, f)
					
				modPkg.Write(nameInPkg, mergeTemp)

				continue
			except:
				print("Tried to parse a non-json asset '"+vanillaPath+"'")
		else:
			#print("Loading '"+nameInPkg+"' from '"+nameOnDisk+"'...")
			modPkg.Write(nameInPkg, nameOnDisk)
	print("Mod assets loaded!")

	if includeVanilla:
		print("Loading vanilla assets...")
		for nameInPkg, nameOnDisk in WalkAssets(modDir, vanillaAssets):
			#print("Loading '"+nameInPkg+"' from '"+nameOnDisk+"'...")
			modPkg.WriteIfAbsent(nameInPkg, nameOnDisk)
		print("Vanilla assets loaded!")

	return modPkg

def PackageAssetbundles(modDir, modSettings, modFile, type):
	modAssets = modDir / "Mod"
	subPkgFileName = str(modSettings["name"]+".jet");
	subPkgPath = tempdir / subPkgFileName;
	subPkg = PackageJet(modDir, modSettings, subPkgPath, type, includeVanilla=False)
	print("Compiling AssetBundle package...")
	subPkg.Store()

	packagesJson = {
		"packages": [
			subPkgFileName
		]
	}
	packagesPath = tempdir / "packages.json";
	with packagesPath.open('w') as f:
		json.dump(packagesJson, f)

	modPkg = Package(modFile, packageType=type, security=None)
	modPkg.Write("AssetBundles/packages.json", str(packagesPath))
	modPkg.Write("AssetBundles/"+subPkgFileName, str(subPkgPath))
	return modPkg

def PackageMod(modName):
	global settings
	modDir = Path(modName)
	if not modDir.exists():
		print("No such mod "+modName+" exists")
		return
	modSettings = ReadModConf(modName)
	modFmt = input("""What format should your mod be packaged to?
NOTE: It's not wise to distribute copyrighted material!
	To avoid this, package your mod using either 'nkh' format, or 'AssetBundles' format!

1. nkh
	A mod format that takes full advantage of NKHook5's features.
	REQUIRES NKHook5
	Slowest build, smallest file size
2. jet
	The vanilla assets format.
	Does not support NKHook5 features.
	DOES NOT require NKHook5. 
	Slow build, large file size
3. AssetBundles
	Another vanilla asset format.
	Does not support NKHook5 features.
	Typically does not require the user to replace or modify any game files
	DOES NOT require NKHook5
	Fast build, large file size
4. Unpacked
	Leaves all files unpacked, outside of any archives.
	MUST BE EXTRACTED BY USER
	DOES NOT require NKHook5
	Fastest build, largest file size
(1-4): """)

	fileExt = ".zip"
	if str(modFmt) == str(1):
		modFmt = "nkh"
		fileExt = ".nkh"

	if str(modFmt) == str(2):
		modFmt = "jet"
		fileExt = ".jet"

	if str(modFmt) == str(3):
		modFmt = "assetbundles"
		fileExt = ".zip"

	if str(modFmt) == str(4):
		modFmt = "unpacked"
		fileExt = ".zip"

	print("Packaging mod '"+modSettings["name"]+"'...'")
	modPkg = None
	if modFmt == "jet":
		modPkg = PackageJet(modDir, modSettings, modSettings["name"]+fileExt, modFmt)
	if modFmt == "assetbundles":
		modPkg = PackageAssetbundles(modDir, modSettings, modSettings["name"]+fileExt, modFmt)
	if modFmt == "unpacked":
		modPkg = PackageUnpacked(modDir, modSettings, modSettings["name"]+fileExt, modFmt)
	print("Compiling package...")
	modPkg.Store()
	print("Mod package complete!")


parser = argparse.ArgumentParser("NKHook5 MDK")
parser.add_argument("--setup", help="Setup your MDK", action='store_true')
parser.add_argument("--dump-assets", help="Dump BTD5 assets", action='store_true')
parser.add_argument("--create-mod", help="Create a new BTD5 mod")
parser.add_argument("--update-mod", help="Updates a mod to the latest dumped version")
parser.add_argument("--editor", help="Opens Visual Studio Code with the specified mod as the workspace")
parser.add_argument("--run-mod", help="Opens Bloons TD 5 with the specified mod")
parser.add_argument("--make-git", help="Makes a git repository for a specified mod")
parser.add_argument("--remote", help="Specifies an upstream remote for the new git repo")
parser.add_argument("--clone-git", help="Clone a mod from a remote repository")
parser.add_argument("--package", help="Packages a mod into a single file that can be used by an NKHook5 user")
args = parser.parse_args()
ReadConf()

if args.setup:
	Setup()
if args.dump_assets:
	DumpAssets()
if not args.create_mod == None:
	CreateMod(args.create_mod)
if not args.update_mod == None:
	UpdateMod(args.update_mod)
if not args.editor == None:
	OpenEditor(args.editor)
if not args.run_mod == None:
	RunMod(args.run_mod)
if not args.make_git == None:
	MakeGit(args.make_git, args.remote)
if not args.package == None:
	PackageMod(args.package)