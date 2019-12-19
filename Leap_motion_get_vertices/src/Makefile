
CC = g++ -std=c++11

INCLUDE = -I/usr/local/include/GLFW -I../include/

LIBS = -Wall -lglfw3 -lm -lGLEW -lGL -lGLU -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread -lSOIL -lassimp
LEAP_LIBRARY := ../lib/x64/libLeap.so -Wl,-rpath,../lib/x64 -lz

# enter filename without extension
FILENAME = main
FILENAME1 = gamesettings
FILENAME2 = modelloader
FILENAME3 = shader

all: $(FILENAME).cpp
	$(CC) -Wall -g $(INCLUDE_LEAP) ../include/${FILENAME3}.cpp ../include/${FILENAME2}.cpp ../include/${FILENAME1}.cpp $(FILENAME).cpp -o ../bin/$(FILENAME) $(LIBS) $(LEAP_LIBRARY)

run:
	@../bin/$(FILENAME)

clean:
	rm ../bin/$(FILENAME) 

