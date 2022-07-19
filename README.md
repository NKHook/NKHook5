# NKHook5
A modification for Bloons TD 5 that focuses on bugfixes & performance improvements to encourage the future of BTD5 modding. NKHook5 (NKH5) provides an API modders can use, however right now it is rather incomplete and the main focus of the project is performance improvements for BTD5 as well as removing limitations on .jet modding. Examples of limitations that NKH5 can overcome include the limitation of 1 mod at a time, as well as the inability to inject brand new tower types into the game.

# Progress
A checklist of progress (Will change as the project grows)
```
✅ Loader/Injector
	✅ Proxy DLL
	✅ NKHook5.dll injector
✅ Code hooking
	✅ PolyHook2 setup
	✅ Patch system
❌ Class re-creations
	Now managed by BTD5-Decomp
❌ Game hooks
	✅ CBloonsTD5Game::CBloonsTD5Game()
	✅ CBasePositionableObject::CBasePositionableObject()
	❌ CBaseTower::Upgrade(...)
	❌ CFlagToStringConvertor::FlagToString(...)
	❌ CFlagToStringConvertor::StringToFlag(...)
	...
```

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

# Contributing
Code quality will never be perfect, but we can strive to follow a standard. Here is the current standard and how you should organize your code.

### C# style namespaces
In all aspects, use C# style namespaces, where the namespace is the location of the file.
Example:
The code inside the file ```NKHook5/Patches/CBloonsTD5Game/Constructor.h```
must be inside the namespace
```NKHook5.Patches.CBloonsTD5Game```

This style applies to *all* files.

Due to lengthy namespaces, code such as ``using namespace NKHook5::Patches`` *is* allowed, however avoid when possible.

### Naming
A C#-like naming convention is used in both C# and C++ code throughout the project. All classes, namespaces and functions are always "UpperCamelCase" (CamelCase starting with a capital) while fields and properties are always "camelCase" (or lowerCamelCase, camelCase starting with a lower case letter).

In C++, all functions have trailing return types.
Example:
```
int Add(int a, int b)
{
    return a+b;
}
```
would be
```
auto Add(int a, int b) -> int
{
    return a+b;
}
```

### Brackets
"Curley brackets" ('{', '}') are always on the next line and never on the same line (as seen above).

### Header guarding
All header files should be header guarded like so:
```
#ifndef FILE_PATH_SEPERATED_BY_UNDERSCORES //(file/path/seperated/by/underscores.h)
#define FILE_PATH_SEPERATED_BY_UNDERSCORES //(file/path/seperated/by/underscores.h)

//Content

#endif /* FILE_PATH_SEPERATED_BY_UNDERSCORES //(file/path/seperated/by/underscores.h) */
```

### Exceptions
Hook callbacks, game functions, etc will be given exceptions to these rules due to the fact they usually need to be very close to the game's code if not the exact same. However, if its possible to stick to these conventions, please do.

If code is spotted not following this standard, let us know so it can be fixed.