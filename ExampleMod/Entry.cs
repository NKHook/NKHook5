using NKHook5;
using System;

namespace ExampleMod
{
    public class Entry : BTDModStart
    {
        public void OnModLoaded()
        {
            Console.WriteLine("Hello from Mod!");
        }
    }
}