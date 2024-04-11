#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iomanip>
#include "Playlist.h"
using namespace std;
int findIn(Playlist* list, int id) {
    for(int i=0;i<list->getSize();++i){
		 if(list->at(i).getId()==id){
			 return i;
		 }
	 }
	return -1;
}
/*int findIn(vector<Song> vec, int id) {
    for(int i=0;i<vec.size();++i){
		 if(vec.at(i).getId()==id){
			 return i;
		 }
	 }
	return -1;
}*/
int findInP(vector<Playlist*> vec, int id) {
    for(int i=0;i<vec.size();++i){
		 if(vec.at(i)->getId()==id){
			 return i;
		 }
	 }
	return -1;
}

int main(int argc, char *argv[]) {
	string input = "";
	vector<string> inputWords;
	Playlist *allSongList= new Playlist();
	//vector<Song> allSongList;
	vector<int> allIds;
	vector<Playlist*> allPlaylists;
	while (true) {
		cout << setfill(' ');
		cout << "Enter [\"song <songid> <artist> <duration> <title>\"]" << endl;
		cout << setw(7) << left << " " << "\"remove <songid>\"" << endl;
		cout << setw(7) << left << " " << "\"playlist <playlistid> <name>\"" << endl;
		cout << setw(7) << left << " " << "\"add <songid> <playlistid>\"" << endl;
		cout << setw(7) << left << " " << "\"drop <songid> <playlistid>\"" << endl;
		cout << setw(7) << left << " " << "\"seesong <songid>\"" << endl;
		cout << setw(7) << left << " " << "\"seeplaylist <playlistid>\"" << endl;
		cout << setw(7) << left << " " << "\"deleteplaylist <playlistid>\"" << endl;
		cout << setw(7) << left << " " << "\"copyplaylist <playlistid> <new playlistid> <new playlist name>\"" << endl;
		cout << setw(7) << left << " " << "\"renameplaylist <playlistid> <new playlist name>\"" << endl;
		cout << setw(7) << left << " " << "\"quit\"]" << endl;
		cout << ": ";

		getline(cin,input);
		
		if(input == "quit"){
			return 0;
		}
		string word = "";
		input+=' ';
		bool song=false;
		bool playlistname=false;
		
		for(int i=0;i<input.length();++i){
			if(input[i] == ' '){
				inputWords.push_back(word);
				if (word=="song"){
					song=true;
				}
				if (word=="renameplaylist" || word=="copyplaylist" || word=="playlist"){
					playlistname=true;
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
			if(playlistname && input[i]=='"'){
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
				//cout <<word<<endl;
				word = "";
				i=end+1;
			}
			else{
				word+=input[i];
			}
		}
		if(inputWords[0] == "song" && inputWords.size()>=5){
			bool time=true;
			bool idint=true;
			bool iduni=true;
			int id=0;
			int foundPrev=0;
			int duration=0;
			for(char c:inputWords[3]){
				if(!isdigit(c)){
					time=false;
					break;
				}
			}
			for(char c:inputWords[1]){
				if(!isdigit(c)){
					idint=false;
					//iduni=false;
					break;
				}
			}
			if(idint){
				id=stoi(inputWords[1]);
				foundPrev=findIn(allSongList, id);
				if(foundPrev>=0){
					iduni=false;
				}
			}
			
			if(!time){cout << "duration " << inputWords[3] << " is not an integer" << endl;}
			if(!idint){cout << "song id " << inputWords[1] << " is not an integer" << endl;}
			if(!iduni){cout << "song id " << id << " already used for ";
						  cout << allSongList->at(foundPrev).getTitle() << " by ";
						  cout << allSongList->at(foundPrev).getArt() << endl;	
						 }
			//cout<<iduni<<endl;
			if(time && idint && iduni){
				duration = stoi(inputWords[3]);
				int min = duration/60;
				int sec = duration % 60;

				//create song
				Song addSong(id, inputWords[4],duration,inputWords[2]);
				//add to global & id list
				allSongList->add(addSong);
				allIds.push_back(addSong.getId());
				
				if (duration < 60) {sec=time;}
				cout << "new song " << inputWords[4] << " by " << inputWords[2] << " " << min << ':';
				if(sec<10){cout<<0;}
				cout << sec << endl;
			}
			//cout << "total songs " << allSongList.size() << endl;
			//inputWords.clear();
		}
			
		else if(inputWords[0] == "remove" && inputWords.size()>=2){
			cout << "removing song " << inputWords[1] << endl;
			bool idint=true;
			int id=0;
			int foundPrev=0;
			for(char c:inputWords[1]){
				if(!isdigit(c)){
					idint=false;
					cout << "song id " << inputWords[1] << " is not an integer" << endl;
					break;
				}
			}
			if(idint){
				id=stoi(inputWords[1]);
				foundPrev=findIn(allSongList, id);
				//cout<<foundPrev<<endl;
				if(foundPrev<0){
					cout << "song " << id << " does not exist" << endl;
				}else{
					cout << "song " << id << ", " << allSongList->at(foundPrev).getTitle() << " by ";
					cout << allSongList->at(foundPrev).getArt() << ", removed" << endl;
					for(int i=0;i<allPlaylists.size();++i){
						if(allPlaylists.at(i)->has(allSongList->at(foundPrev))){
							allPlaylists.at(i)->remove(allSongList->at(foundPrev));
						}
					}
					allSongList->del(foundPrev);
					
					//cout<<allSongList.size()<<endl;
				}
			}
			//inputWords.clear();
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
