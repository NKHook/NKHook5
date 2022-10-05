add_subdirectory(Documents)
add_subdirectory(Images)

target_sources(Common PRIVATE
	"SpriteExtract.cpp"
	"SpritePack.cpp"
)