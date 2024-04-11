#include <iostream>
#include <stdlib.h>
#include "Song.h"
using namespace std;

Song::Song(int idin, string titlein, int timein, string artistin){
   id=idin;
	title=titlein;
	time=timein;
	artist=artistin;
}
Song::Song(){
   id=0;
	title="";
	time=0;
	artist="";
}
// Copy assignment 
Song& Song::operator=(const Song& other) {
	if (this != &other) {
        // Copy data members from other to the current object
        this->id = other.id;
        this->title = other.title;
        this->time = other.time;
        this->artist = other.artist;
    }
    return *this;
}

// Destructor
Song::~Song() {
}

int Song::getId() {
	return id;
}
string Song::getTitle() {
	return title;
}
int Song::getTime() {
	return time;
}
string Song::getArt() {
	return artist;
}
void Song::show() {
	cout << "song " << id << " " << title << " by " << artist << endl;
}
void Song::setTitle(string titlein) {
	title=titlein;
}
void Song::setTime(int timein) {
	time=timein;
}
void Song::setArt(string artistin) {
	artist=artistin;
}


