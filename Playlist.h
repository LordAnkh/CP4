#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Song.h"

using namespace std;

class Playlist{
   public:
		Playlist();
		/*Playlist(const Playlist& origObject); // Copy constructor
		Playlist& operator=(const Playlist& objToCopy); //copy assignment operator
		*/
		~Playlist();

		void clear(Song* song);
		Song* getSong(string title);
		void insert(Song* song);
		void remove(Song song);
		int getIdIndex(Song* song);

		//binary heap funcs
		void heapify(int i);
		void heapRemove(int i);
		int percUp(int i); //item at i gets percolated up
		void insertHeap(Song& song);
		int percDown(int i); //item at i getes percolated down
		
		void show(Song*root); //inorder traversal
		Song* root;
		//Song* copy();
		vector<Song*> heap;
		
};

