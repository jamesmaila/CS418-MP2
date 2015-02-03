# Object files
OBJS = mp2.o camera.o vector.o

# EXE name
EXENAME = mp2

# Macro assignments
CC = g++
CCOPTS = -c -g -O0 -Wall 
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# The main compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) -lglut -lGLU -lGL

# Compiles object files.
mp2.o : mp2.cpp 
	$(CC) $(CCOPTS) mp2.cpp

camera.o : camera.cpp
	$(CC) $(CCOPTS) camera.cpp

vector.o : vector.cpp
	$(CC) $(CCOPTS) vector.cpp
	
# Clean
clean : 
	rm -f *.o $(EXENAME) 2>/dev/null
