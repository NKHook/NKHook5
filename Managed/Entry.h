#include "BTDModStart.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;

namespace NKHook5
{
    namespace Managed
    {
    public ref class Entry
    {
        public:
            static void Main()
            {
                Console::WriteLine("NKHook6-Managed loading...");

                AppDomain^ appDomain = AppDomain::CurrentDomain;

                if(!Directory::Exists("Mods"))
                {
                    Directory::CreateDirectory("Mods");
                }

                for each(String^ filePath in Directory::EnumerateFiles("Mods", "*.dll"))
                {
                    Console::WriteLine("Loading "+filePath);

                    try
                    {
                        /*FileStream^ fs = gcnew FileStream(filePath, FileMode::Open);
                        array<Byte>^ buffer = gcnew array<Byte>((int)fs->Length);
                        fs->Read(buffer, 0, buffer->Length);
                        fs->Close();*/

                        Assembly^ assembly = Assembly::LoadFrom(filePath);

                        Console::WriteLine("Assembly loaded");
                        for each(Type^ type in assembly->GetTypes())
                        {
                            Console::WriteLine(type);
                            if(BTDModStart::typeid->IsAssignableFrom(type))
                            {
                                BTDModStart^ modEntry = (BTDModStart^)Activator::CreateInstance(type);
                                modEntry->OnModLoaded();
                            }
                        }
                    }
                    catch(Exception^ ex)
                    {
                        Console::WriteLine(ex);
                    }
                }

                Console::WriteLine("NKHook6-Managed loaded!");
            };
        };
    }
};