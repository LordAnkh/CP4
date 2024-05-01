#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Song {
   public:
    Song(Song* parentin,Song* lef,Song* righ, string titlein, int timein,int idin);
	Song();
	
	void setTitle(string newtitle);
	string Title();
	void setTime(int newtime);
	int Time();
	void setId(int idin);
	int Id();
	string show();

	
	
	
	int heapIndex=0;

	
	Song* parent;
	Song* left;
	Song* right;
	bool remove=false;
	bool favorite=false;
	private:
 
	string title;
	int runningtime;
	int id;

};