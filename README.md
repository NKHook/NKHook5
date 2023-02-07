# NKHook5
A modification for Bloons TD 5 that focuses on bugfixes & performance improvements to encourage the future of BTD5 modding. NKHook5 (NKH5) provides an API modders can use, however right now it is rather incomplete and the main focus of the project is performance improvements for BTD5 as well as removing limitations on .jet modding. Examples of limitations that NKH5 can overcome include the limitation of 1 mod at a time, as well as the inability to inject brand new tower types into the game.

# Progress
A checklist of progress (Will change as the project grows). Details the things NKHook5 aims to fix or add to the game. This list includes bugs that remain unpatched. [All to-do items from BTD5Patcher](https://github.com/DisabledMallis/BTD5Patcher/projects/1) are now going to be part of the base NKHook5 project. Issues may be opened for feature requests, and will be given the "Planned" tag if accepted.

# Startup list
NKHook5 changes how Bloons TD 5 loads in a few ways, heres a list comparing vanilla to NKH5.

### Vanilla loading
```
	1. Exe is executed
	2. Windows loads necessary libraries
	3. Game execution begins
	4. Exe initializes CBloonsTD5Game
```
### NKHook5 loading
```
	1. Exe is executed
	2. Windows loads necessary libraries
	3. NKHook5 fakes being a needed library
	4. NKHook5 loads
	5. Patches are applied
	6. Game execution begins
	7. Exe starts initializing CBloonsTD5Game
	8. NKHook5 initialization begins
	9. Mods are loaded & executed
	10. CBloonsTD5Game continues being initialized
```

# Installing NKHook5
1. Download wininet.dll (This is the bootstrapper)
2. Download NKHook5.dll (This is the mod loader)
3. Copy wininet.dll into your game's folder
4. Copy NKHook5.dll into your game's folder
5. Create a "Mods" folder in your game's folder