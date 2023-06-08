#OBJS specifies which files to compile as part of the project
OBJS = src/maze.c src/actions.c


#CC specifes which compiler we're using
CC = gcc -std=gnu89

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#  -I where to find include files
COMPILER_FLAGS = -w -I/usr/include/SDL2 -Iinc  -D_REENTRANT

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2  -lm

#OBJ_NAME specifies the name of our executable
OBJ_NAME = maze



#This is the target that compiles our executable
all:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
