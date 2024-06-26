#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iomanip>
#include "Playlist.h"
using namespace std;
/*int findIn(vector<Song> vec, int id) {
    for(int i=0;i<vec.size();++i){
		 if(vec.at(i).getId()==id){
			 return i;
		 }
	 }
	return -1;
}*/
void addId(vector<Song>&allIds, Song& song){
	int id=song.Id();
	int i=0;
	if(allIds.size()==0){allIds.push_back(song);song.vecIndex = 0;return;}
	for(i=0;i<allIds.size();i++){
		if(song.Id()<=allIds[i].Id()){
			break;
		}
	}
	allIds.insert(allIds.begin() + i, song);
	song.vecIndex = i;
}

int main(int argc, char *argv[]) {
	vector<string>inputWords;
	string input = "";
	Playlist *songsByTitle= new Playlist();
	//vector<Song> allSongList;
	vector<Song> allIds;
	vector<Song>favorites;
	
	while (true) {
		/*cout << setfill(' ');
		cout << "Enter [\"song <songid> <artist> <duration> <title>\"]" << endl;
		cout << setw(7) << left << " " << "\"listen <song-title> <seconds>\"" << endl;
		cout << setw(7) << left << " " << "\"favorite\"" << endl;
		cout << setw(7) << left << " " << "\"remove <song-title>\"" << endl;
		cout << setw(7) << left << " " << "\"show_listen_time\"" << endl;
		cout << setw(7) << left << " " << "\"quit\"]" << endl;
		cout << ": ";*/
		getline(cin,input);
		
		if(input == "quit"){
			return 0;
		}
		string word = "";
		input+=' ';
		bool song=false;
		bool remove=false;
		bool playlistname=false;
		
		for(int i=0;i<input.length();++i){
			if(input[i] == ' '){
				inputWords.push_back(word);
				if (word=="song"){
					song=true;
				}
				if (word=="remove"){
					remove=true;
				}
				//cout <<word<<endl;
				word = "";
				i++;
			}
			if(song && inputWords.size()==4 && input[i]=='"'){
				word=input.substr(i+1, input.length()-3-i);
				inputWords.push_back(word);
				//cout <<word<<endl;
				word = "";
				i+=input.length();
			}
			if(remove && inputWords.size()==1 && input[i]=='"'){
				word=input.substr(i+1, input.length()-3-i);
				inputWords.push_back(word);
				//cout <<word<<endl;
				word = "";
				i+=input.length();
			}
			if(song && inputWords.size()==2 && input[i]=='"'){
				int end=input.length()-1;
				i+=1;
				for(int j=i;j<input.length();++j){
					if(input[j]=='"'){
						end=j;
						//cout <<end<<endl;
						j+=input.length();
					}
				}
				word=input.substr(i, end-i);
				inputWords.push_back(word);
				//cout <<input[end]<<endl;
				word = "";
				i=end+2;
			}
			else{
				word+=input[i];
			}
		}
		if(inputWords[0] == "song" && inputWords.size()>=5){
			int id;
			int listen=0;
			int min=0;
			int sec=0;
			try {
				id=stoi(inputWords[1]);
				listen= stoi(inputWords[3]);
				min = listen/60;
				sec = listen % 60;
				
			Song*newSong=new Song();
			newSong->setId(id);
			newSong->setTitle(inputWords[4]);
			addId(allIds,*newSong);
			songsByTitle->insertHeap(*newSong);
			songsByTitle->insert(newSong);
			//cout<<newSong->heapIndex<<endl;
			cout<<"new song "<<id<<" "<<inputWords[4]<<" by "<<inputWords[2]<<" "<<min<<":"<<sec;
			if(sec==0){cout<<0;}cout<<endl;
			} catch (...) {
				std::cout << "Invalid input." << std::endl;
			}
		}
		else if(inputWords[0] == "remove" && inputWords.size()>=2){
			//cout << "removing song " << inputWords[1] << endl;
			Song *getSong=songsByTitle->getSong(inputWords[1]);
			if(getSong!=nullptr){
				int vecIndex=getSong->vecIndex;
				//cout<<vecIndex<<endl;
				Song *newSong=new Song();
				newSong->setTitle(inputWords[1]);
				allIds[vecIndex].remove=true;
				//cout<<getSong->heapIndex<<endl;
				//cout<<"heap sizebf "<<songsByTitle->heap.size()<<endl;
				//cout<<"heapind "<<getSong->heapIndex<<endl;
				songsByTitle->heapRemove(getSong->heapIndex);
				//cout<<"heap sizeaf "<<songsByTitle->heap.size()<<endl;
				//cout<<"heapsize "<<songsByTitle->heap.size()<<endl;
				if(getSong->favorite){
					cout << "Removed " << inputWords[1]<<" from your favorites" << endl;
				}else{
					cout << "Removed " << inputWords[1]<<" from your songs" << endl;
				}
				songsByTitle->remove(*getSong);
				
			}else{cout<<inputWords[1]<<" is not a valid song"<<endl;}
			//cout<<allIds<<endl;
		}
		else if(inputWords[0] == "show_listen_time" && inputWords.size()>=1){
			//songsByTitle->show(songsByTitle->root);
			for(int i=0;i<allIds.size();i++){
				if(!allIds[i].remove){
					allIds[i].show();
				}
			}
		}
		else if(inputWords[0] == "favorite" && inputWords.size()>=1){
			if(songsByTitle->heap.size()>0){
				favorites.push_back(*songsByTitle->heap[0]);
				songsByTitle->heap[0]->favorite=true;
				cout<<"Song "<<songsByTitle->heap[0]->Title()<<" added to list of favorites (Listened for "<<songsByTitle->heap[0]->Time()<<" seconds)"<<endl;
				songsByTitle->heapRemove(0);
				//cout<<"heapsize "<<songsByTitle->heap[0].Title()<<endl;
			}
			else{cout<<"No song to favorite"<<endl;}
		}
		else if(inputWords[0] == "listen" && inputWords.size()>=3){
			int listen=0;
			
			Song *newSong=songsByTitle->getSong(inputWords[1]);
			//songsByTitle->show(songsByTitle->root);
			if(newSong==nullptr){cout<<"nullptr"<<endl;}

			bool validtime=false;
			bool favorite=false;
			try {
				listen= std::stoi(inputWords[2]);
				validtime=true;
			} catch (...) {
				std::cout << inputWords[2] << "is not a valid time." << std::endl;
			}
			if(newSong!=nullptr&&validtime){
				int time=newSong->Time();
				int updateTime=time+listen;
				newSong->setTime(updateTime);
				allIds[newSong->vecIndex].setTime(updateTime);
				//if(newSong->heapIndex!=-1){
				for(int i=0;i<favorites.size();i++){
					if(favorites[i].Title()==newSong->Title()){favorite=true;}
				}
				//}
				if(!favorite){
					//cout<<newSong->Title()<<" "<<newSong->heapIndex<<endl;
					/*cout<<"heap to be changed: ";
					for(int i=0;i<songsByTitle->heap.size();i++){
						cout<<songsByTitle->heap[i]->Title()<<":"<<songsByTitle->heap[i]->heapIndex<<" ";
					}cout<<endl;*/
					songsByTitle->heapRemove(songsByTitle->getSong(inputWords[1])->heapIndex);
					
					songsByTitle->insertHeap(*songsByTitle->getSong(inputWords[1]));
					/*for(int i=0;i<songsByTitle->heap.size();i++){
						cout<<songsByTitle->heap[i]->Title()<<":"<<songsByTitle->heap[i]->heapIndex<<" ";
					}cout<<endl;*/
					//cout<<newSong->Title()<<" "<<newSong->Time()<<endl;
					//cout<<"after add heap "<<newSong->heapIndex<<endl;
					//cout<<"heap size "<<songsByTitle->heap.size()<<endl;
					/*cout<<"heap after: ";
					for(int i=0;i<songsByTitle->heap.size();i++){
						cout<<songsByTitle->heap[i]->Title()<<":"<<songsByTitle->heap[i]->heapIndex<<" ";
					}cout<<endl;*/
					cout<<"Listened to "<<inputWords[1]<<" for "<<inputWords[2]<<" seconds."<<endl;
					
				}else{
					cout<<"Song "<<inputWords[1]<<" is a favorite."<<endl;
				}
			}else if(newSong==nullptr){
				cout<<inputWords[1]<<" is not a valid song."<<endl;
			}
		}
		else if(input!= " "){
			cout << "Command not recognized, please try again." << endl;
			//inputWords.clear();
		}
		inputWords.clear();
	}
	inputWords.clear();
	return 0;
}
