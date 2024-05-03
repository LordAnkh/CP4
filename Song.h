#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Song {
   public:
    Song(string titlein, int timein,int idin);
	Song();
	
	void setTitle(string newtitle);
	string Title();
	void setTime(int newtime);
	int Time();
	void setId(int idin);
	int Id();
	void show();

	
	
	
	

	
	Song* parent;
	Song* left;
	Song* right;
	int heapIndex=-1;
	int vecIndex=0;
	bool remove=false;
	bool favorite=false;
	int key;
	private:

	string title;
	int runningtime;
	int id;

};
//#include "Song.cpp"
#endif
