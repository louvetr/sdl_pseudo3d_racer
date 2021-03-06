#.PHONY: using-gcc using-gcc-static using-clang

#OBJS specifies which files to compile as part of the project
OBJS = 	./src/main.c	\
		./src/event.c 	\
		./src/display.c	\
		./src/display_race.c	\
		./src/display_menu.c	\
		./src/logic.c	\
		./src/road.c	\
		./src/track.c	\
		./src/cars_ai.c	\
		./src/gfx.c	\
		./src/sound.c

#CC specifies which compiler we're using
CC = gcc

INC=-I${CURDIR}/include

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#COMPILER_FLAGS = -Wall -ggdb -gdwarf-2
COMPILER_FLAGS = -Wall -Wconversion -ggdb -gdwarf-2
#COMPILER_FLAGS = -Wall -fsanitize=address -O1 -fno-omit-frame-pointer -ggdb -gdwarf-2

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lasan

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = sdl_pseudo3d_racer

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)