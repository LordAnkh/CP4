#include <iostream>
#include <stdlib.h>
#include "Song.h"

using namespace std;

class Playlist{
   public:
		Playlist();
		/*Playlist(const Playlist& origObject); // Copy constructor
		Playlist& operator=(const Playlist& objToCopy); //copy assignment operator
		*/
		~Playlist();

		Song* getSong(String title);
		void insert(Song song);
		void remove(Song song);
		int getIdIndex(Song song);

		//binary heap funcs
		void heapify();
		void percUp(int i);
		void insertHeap(Song song);
		void percDown(int i);
		
		void show(); //inorder traversal
		//Song* copy();
	private:
		Song* root;
		vector<Song> heap;
		
};

