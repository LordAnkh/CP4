#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

class Song {
   public:
      Song(int idin, string titlein, int timein, string artistin);
      Song();
		Song& operator=(const Song& objToCopy); //copy assignment operator
		~Song();

		int getId();
		string getTitle();
		string getArt();
		int getTime();

		void show();
		void setTitle(string titlein);
		void setArt(string artin);
		void setTime(int timein);
	private:
      string title;
		int time;
      string artist;
		int id;

};

