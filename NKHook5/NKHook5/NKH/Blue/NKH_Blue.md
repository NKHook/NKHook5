# NKH Blue
NKH Blue is the 2nd layer to NKHook5. Its a ChaiScript api for NKHook5. The name comes from the Blue bloon in Bloons TD 5.

## Getting started
As mentioned above, NKHook5 uses a scripting language called "ChaiScript" for plugins. This scripting language is very simple to use and this page will guide you through the entire process of making a plugin with ChaiScript.

Assuming you have NKHook5 set up, lets begin!

## Creating your first plugin
Lets begin by naming our plugin. Im going to call mine "TutorialPlugin". Once you have a name decided, inside your NKHook5 plugins folder, create a file for your plugin named in this format: ``<name>.chai``

Nice! your plugin file is created!

## Adding tower types
NKH allows you to inject new tower types to BTD5, we can do this with ChaiScript.

NKH defines a function for this called ``injectFlag``. This function injects a new flag into the game for our custom tower to use.

Example of injectFlag:
```
injectFlag("CustomMonkey", 0x4001)
```

The first parameter ("CustomMonkey") is our tower type. This is often seen in the .jet file as "FactoryName" or "TypeName". In the game's code this is referred to as a "Flag" or "FlagString", so I will call it that for this tutorial.
The second parameter is the ID/Flag. This must be unique, as if it isnt it could cause some serious issues with other mods or straight up just crash the game.

To use this in your plugin, you can simply copy the example into your file. NKHook will fild the file and automatically load it.

## Scripting
NKH allows a lot more than just adding towers. NKH features events in it's ChaiScript api that can be used to change game logic. For example, you could write a script that takes away money instead of health when a bloon escapes. You can find an example of this feature [here](https://github.com/TDToolbox/BTD-Docs/blob/master/md/BTD5%20Engine/btd5/NKHook5/Events/Events.md)

Each plugin has their own thread, meaning you can create "while(true)" loops without freezing the game, however using one in a game thread (such as on an event) will cause the game to freeze.

You can also modify, add or remove scripts from the game without closing or crashing it. The console window can be typed into. Use the "reload" command to make NKHook kill all script threads, remove all script hooks and then load in any new scripts or modified ones. This is helpful in cases where you make small mistakes, you can simply reload and make fixes.