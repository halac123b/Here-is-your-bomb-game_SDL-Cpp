SOURCE = main.cpp CommonFunc.cpp BaseObject.cpp Menu.cpp TextObject.cpp Soldier.cpp TeamObject.cpp Timer.cpp Bomb.cpp SDL2_gfxPrimitives.c SDL2_rotozoom.c ExplosionObject.cpp Sound.cpp
all:
	g++ -Isrc/include -Lsrc/lib -o main $(SOURCE) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

