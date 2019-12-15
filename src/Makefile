
CC = g++ -std=c++11

INCLUDE = -I/usr/local/include/GLFW -I../include/

LIBS = -Wall -lglfw3 -lm -lGLEW -lGL -lGLU -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread -lSOIL
LEAP_LIBRARY := ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64 -lz

# enter filename without extension
FILENAME = main

all: $(FILENAME).cpp
	$(CC) -Wall -g $(INCLUDE_LEAP) $(FILENAME).cpp -o ../bin/$(FILENAME) $(LIBS) $(LEAP_LIBRARY)

run:
	@./$(FILENAME)

clean:
	rm ./$(FILENAME) 

