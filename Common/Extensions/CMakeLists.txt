target_sources(Common PRIVATE
	"Extension.cpp"
	"ExtensionManager.cpp"
	"JsonExtension.cpp"
)

add_subdirectory(Generic)
add_subdirectory(Tower)
add_subdirectory(Weapon)