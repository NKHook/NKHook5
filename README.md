# NKHook5
A mod loader for Bloons TD 5 that greatly extends modding capabilities

# Installing NKHook5
1. Download wininet.dll (This is the bootstrapper)
2. Download NKHook5.dll (This is the mod loader)
3. Copy wininet.dll into your game's folder
4. Copy NKHook5.dll into your game's folder
5. Create a "Mods" folder in your game's folder

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
