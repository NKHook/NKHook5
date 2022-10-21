add_subdirectory(Json)
add_subdirectory(Xml)

target_sources(Common PRIVATE
	"Glob.cpp"
	"Timer.cpp"
)