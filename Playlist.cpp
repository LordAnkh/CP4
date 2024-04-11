#include <iostream>
#include <stdlib.h>
#include "Playlist.h"
using namespace std;

Playlist::Playlist(){
	array=new Song[2];
	size=1;
	capacity=size;
	id=0;
	title="";
}
// Copy constructor
Playlist::Playlist(const Playlist& origObject) {
   size = origObject.size;
	capacity = origObject.capacity;

	// Allocate memory for the array
	array = new Song[size];

	// Copy each song from the original array to the new array
	for (int i = 0; i < size-capacity; ++i) {
		array[i] = origObject.array[i];
	}
}
// Copy assignment 
Playlist& Playlist::operator=(const Playlist& other) {
	if (this != &other) {
		size = other.size;
		capacity = other.capacity;

		delete[] array;
		
		array = new Song[capacity];

		for (int i = 0; i < size; ++i) {
			array[i] = other.array[i];
		}
	}
	return *this;
}

// Destructor
Playlist::~Playlist() {
   delete[] array;
}

int Playlist::getSize() {
	return size-capacity;
}
int Playlist::getCap() {
	return capacity;
}
bool Playlist::has(Song song){
	for(int i=0;i<size-capacity;i++){
		if(array[i].getId()==song.getId()){
			return true;
		}
	}
	return false;
}
void Playlist::add(Song song){
	//cout<<"adding song "<<song.getId()<<endl;
	int orig=size;
	if(capacity<1){
		capacity=capacity+size;
		size*=2;
		Song* arr= new Song[size];
		for(int i=0;i<orig;++i){
			arr[i]=array[i];
		}
		delete[] array;
		array=arr;
	}
	int index=0;
	bool max=true;
	for(int i=0;i<orig;i++){
		if(array[i].getId()>song.getId()){
			index=i;
			max=false;
			i+=orig;
		}
	}
	if(max){index=size-capacity;}
	if(size>1&&!max){
		for(int i=size-capacity-1;i>=index;i--){
			//cout<<i<<endl;
			//cout<<array[i].getId()<<endl;
			//cout<<"shift"<<endl;
			array[i+1]=array[i];
		}
	}
	array[index]=song;
	capacity--;
}
Song Playlist::getSong(int index){
	return array[index];
}
void Playlist::del(int index){
	if(size==1){
		capacity=1;
		return;
	}
	for(int i=index+1;i<size-capacity;i++){
		array[i-1]=array[i];
	}
	capacity++;
}
void Playlist::remove(Song song){
	if(size==1){
		capacity=1;
		return;
	}
	int index=0;
	for(int i=0;i<size-capacity;i++){
		if(array[i].getId()==song.getId()){
			index=i;
		}
	}
	for(int i=index+1;i<size-capacity;i++){
		array[i-1]=array[i];
	}
	capacity++;
}
void Playlist::setId(int idin){
	id=idin;
}
Song Playlist::at(int index){
	return array[index];
}
void Playlist::setTitle(string ti){
	title=ti;
}
void Playlist::show(){
	for(int i=0;i<size-capacity;i++){
		array[i].show();
	}
}
int Playlist::getId(){
	return id;
}
string Playlist::getTitle(){
	return title;
}
