S_FILES=OpenNitemare3D/engine/camera/Camera.cpp OpenNitemare3D/engine/dat/Datreader.cpp OpenNitemare3D/engine/entity/Entity.cpp OpenNitemare3D/engine/img/img.cpp OpenNitemare3D/engine/map/Map.cpp OpenNitemare3D/engine/math/Vector2f.cpp OpenNitemare3D/engine/math/Vector2i.cpp OpenNitemare3D/engine/pal/pal.cpp OpenNitemare3D/engine/sound/Music.cpp OpenNitemare3D/engine/sound/Sound.cpp OpenNitemare3D/engine/tiles/Tiles.cpp OpenNitemare3D/game/entities/player/Player.cpp OpenNitemare3D/main.cpp

EXEC=opennitemare3d

CC=g++
CC_SDL=`sdl2-config --cflags --libs` `pkg-config SDL2_mixer --cflags --libs` `pkg-config SDL2_image --cflags --libs` -ggdb

all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)
