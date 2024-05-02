# Specifiy the target
all: listen_up

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
listen_up: listen_up.o Song.o Playlist.o
	g++ listen_up.o Song.o Playlist.o -o listen_up

# Specify how the object files should be created from source files
listen_up.o: listen_up.cpp
	g++ -c listen_up.cpp -o listen_up.o

Song.o: Song.cpp Song.h
	g++ -c Song.cpp -o Song.o

Playlist.o: Playlist.cpp Playlist.h
	g++ -c Playlist.cpp -o Playlist.o

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o listen_up