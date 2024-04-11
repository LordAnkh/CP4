# Specifiy the target
all: cp2_songs

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
cp2_songs: cp2_songs.o Song.o Playlist.o
	g++ cp2_songs.o Song.o Playlist.o -o cp2_songs

# Specify how the object files should be created from source files
cp2_songs.o: cp2_songs.cpp
	g++ -c cp2_songs.cpp -o cp2_songs.o

Song.o: Song.cpp Song.h
	g++ -c Song.cpp -o Song.o

Playlist.o: Playlist.cpp Playlist.h
	g++ -c Playlist.cpp -o Playlist.o

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o cp2_songs