# Create .dll
add_library(ExampleMod SHARED)

# Set the C# language version to 9
set_target_properties(ExampleMod PROPERTIES VS_GLOBAL_LangVersion "9.0")

# Make it target Win32
SET(CMAKE_CSharp_FLAGS "/platform:x86")

# Set project properties
set_property(TARGET ExampleMod PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
set_property(TARGET ExampleMod PROPERTY WIN32_EXECUTABLE FALSE)
set_property(TARGET ExampleMod PROPERTY VS_CONFIGURATION_TYPE ClassLibrary)
set_property(TARGET ExampleMod PROPERTY VS_DOTNET_REFERENCES_COPY_LOCAL OFF)

# Add sources
target_sources(ExampleMod PRIVATE 
    "Entry.cs"
)

# Add Managed as a dependency to build *after* it builds
add_dependencies(ExampleMod Managed)

# Add references
set_property(TARGET ExampleMod PROPERTY VS_DOTNET_REFERENCES
    ${PROJECT_SOURCE_DIR}/Managed/Release/Managed.dll;
)