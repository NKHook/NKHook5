# NKHook5
Latest NKHook5 repository

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

### Exceptions
Hook callbacks, game functions, etc will be given exceptions to these rules due to the fact they usually need to be very close to the game's code if not the exact same. However, if its possible to stick to these conventions, please do.

If code is spotted not following this standard, let us know so it can be fixed.