#include <iostream>
#include <stdlib.h>
#include "Song.h"
using namespace std;

Song::Song(Song* parentin,Song* lef,Song* righ, string titlein, int timein,int idin)
{
parent=parentin;
left=lef;
right=righ;
title=titlein;
runningtime=timein;
id=idin;
}
Song::Song(){
parent=nullptr;
left=nullptr;
right=nullptr;
id=0;
title="";
runningtime=0;
}
	void Song::setTitle(string newtitle)
	{
		title=newtitle;
	}
	string Song::Title()
	{
		return title;
	}
	void Song::setTime(int newtime)
	{
		runningtime=newtime;
	}
	int Song::Time()
	{
		return runningtime;
	}
	void Song::setId(int idin)
	{
		id=idin;
	}
	int Song::Id()
	{
		return id;
	}
	string Song::show()
	{
	cout<< id<<" "<<title<<" has been listened to for "<<runningtime<< " seconds"<<endl; 
	}