#include <iostream>
#include <stdlib.h>
#include "Song.h"

using namespace std;

class Playlist{
   public:
		Playlist();
		Playlist(const Playlist& origObject); // Copy constructor
		Playlist& operator=(const Playlist& objToCopy); //copy assignment operator
		~Playlist();
		
		int getSize();
		int getCap();
		Song getSong(int index);

		bool has(Song song);
		void add(Song song);
		Song at(int index);
		void del(int index);
		void remove(Song song);
		void setId(int idin);
		void setTitle(string ti);
		void show();
		int getId();
		string getTitle();
		//Song* copy();
	private:
		Song* array;
		int size;
		int capacity;
		int id;
		string title;
};

