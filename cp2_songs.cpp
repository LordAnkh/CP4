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
		else if(inputWords[0] == "playlist" && inputWords.size()>=3){
			bool idint=true;
			int id=0;
			string title=inputWords[2];
			for(char c:inputWords[1]){
				if(!isdigit(c)){
					idint=false;
					cout << "playlist id " << inputWords[1] << " is not an integer" << endl;
					break;
				}
			}
			if(idint){
				id=stoi(inputWords[1]);
				Playlist *newList=new Playlist();
				newList->setId(id);
				newList->setTitle(title);
				bool max=true;
				for(int i=0;i<allPlaylists.size();i++){
					if(allPlaylists.at(i)->getId()>id){
						allPlaylists.insert(allPlaylists.begin() + i, newList);
						max=false;
						i+=allPlaylists.size();
					}
				}
				if(max){
					allPlaylists.push_back(newList);
				}
				cout << "new playlist " << inputWords[1] << " called " << inputWords[2] << endl;
			}
			//inputWords.clear();
		}
		else if(inputWords[0] == "add" && inputWords.size()>=3){
			bool pint=true;
			bool sint=true;
			cout << "add song " << inputWords[1] << " to playlist " << inputWords[2] << endl;
			int playlistid=0; int songid=0;
			try {
				playlistid = stoi(inputWords[2]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[2] << " is not an integer." << std::endl;
				pint=false;
			}
			try {
				songid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "song id " << inputWords[1] << " is not an integer." << std::endl;
				sint=false;
			}
			if(pint&&sint){
				int playIndex=findInP(allPlaylists, playlistid);
				int songIndex=findIn(allSongList, songid);
				if(playIndex==-1){
					cout << "playlist " << playlistid << " does not exist" << endl;
				}
				if(songIndex==-1){
					cout << "song " << songid << " does not exist" << endl;
				}
				if(playIndex>-1&&songIndex>-1){
					if(allPlaylists.at(playIndex)->has(allSongList->at(songIndex))){
						cout << "song " << songid << " is already in playlist " << playlistid << endl;
					}
					else {
						allPlaylists.at(playIndex)->add(allSongList->at(songIndex));
						cout << "song " << songid << " successfully added to playlist " << playlistid << endl;
					}
				//cout << allPlaylists.at(playIndex)->getSize() <<endl;
				}
			}
			
			
			//inputWords.clear();
		}
		else if(inputWords[0] == "drop" && inputWords.size()>=3){
			cout << "drop song " << inputWords[1] << " from playlist " << inputWords[2] << endl;
			bool pint=true;
			bool sint=true;
			int playlistid=0; int songid=0;
			try {
				playlistid = stoi(inputWords[2]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[2] << " is not an integer." << std::endl;
				pint=false;
			}
			try {
				songid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "song id " << inputWords[1] << " is not an integer." << std::endl;
				sint=false;
			}
			if(pint&&sint){
				int playIndex=findInP(allPlaylists, playlistid);
				int songIndex=findIn(allSongList, songid);
				if(playIndex==-1){
					cout << "playlist " << playlistid << " does not exist" << endl;
				}
				if(songIndex==-1){
					cout << "song " << songid << " does not exist" << endl;
				}
				if(playIndex>-1 && songIndex>-1){
					if(allPlaylists.at(playIndex)->has(allSongList->at(songIndex))){
						allPlaylists.at(playIndex)->remove(allSongList->at(songIndex));
						cout << "song " << songid << " successfully dropped from playlist " << playlistid << endl;
					}else{cout << "song " << songid << " is not in playlist " << playlistid << endl;}
					//cout << allPlaylists.at(playIndex)->getSize() <<endl;
				}
			}
			//inputWords.clear();
		}
		else if(inputWords[0] == "seesong" && inputWords.size()>=2){
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
				if(foundPrev<0){
					cout << "song " << id << " does not exist" << endl;
				}else{
					allSongList->at(foundPrev).show();
					//cout<<allSongList.size()<<endl;
				}
			}
			//inputWords.clear();
		}
		else if(inputWords[0] == "seeplaylist" && inputWords.size()>=2){
			bool pint=true;
			int playlistid=0; int songid=0;
			try {
				playlistid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[1] << " is not an integer." << std::endl;
				pint=false;
			}
			int pindex=findInP(allPlaylists, playlistid);
			if(pint && pindex>-1){
				cout << "Songs in playlist " << inputWords[1] << endl;
				allPlaylists.at(pindex)->show();
			}
			if(pindex==-1){
				cout << "playlist " << playlistid << " does not exist" << endl;
			}
			
			//inputWords.clear();
		}
		else if(inputWords[0] == "deleteplaylist" && inputWords.size()>=2){
			bool pint=true;
			int playlistid=0;
			try {
				playlistid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[1] << " is not an integer." << std::endl;
				pint=false;
			}
			int pindex=findInP(allPlaylists, playlistid);
			if(pindex!=-1){
				allPlaylists.at(pindex)->~Playlist();
				allPlaylists.erase(allPlaylists.begin() + pindex);
				cout << "playlist " << playlistid << " successfully deleted" << endl;
			}else{cout << "playlist " << playlistid << " does not exist" << endl;}

			
			//inputWords.clear();
		}
		else if(inputWords[0] == "copyplaylist" && inputWords.size()>=4){
			bool pint=true;
			int playlistid=0;
			int nplaylistid=0;
			try {
				playlistid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[1] << " is not an integer." << std::endl;
				pint=false;
			}
			try {
				nplaylistid = stoi(inputWords[2]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[2] << " is not an integer." << std::endl;
				pint=false;
			}
			int pindex=findInP(allPlaylists, playlistid);
			if(playlistid==nplaylistid && pindex>-1){
				cout << "playlist id " <<playlistid<< " already exists" << endl;
			}
			int npindex=findInP(allPlaylists, nplaylistid);
			if(playlistid!=nplaylistid && npindex>-1){
				cout << "playlist id " <<nplaylistid<< " already exists" << endl;
			}
			if(pindex==-1){
				cout << "playlist " <<playlistid<< " does not exist" << endl;
			}
			//cout<<"checks done"<< endl;
			if(playlistid!=nplaylistid && pindex>-1){
				Playlist *newList=new Playlist(*allPlaylists.at(pindex));
				//cout<<"copy construct"<<endl;
				newList->setId(nplaylistid);
				newList->setTitle(inputWords[3]);
				//cout << inputWords[3] <<endl;
				allPlaylists.push_back(newList);
				cout << "playlist " << playlistid << " successfully copied to playlist " << nplaylistid << " " << inputWords[3] << endl;
			}
			//inputWords.clear();
		}
		else if(inputWords[0] == "renameplaylist" && inputWords.size()>=3){
			bool pint=true;
			int playlistid=0;
			try {
				playlistid = stoi(inputWords[1]); // Attempt to convert string to integer
				//cout << "Converted integer: " << num << std::endl;
			} catch (const std::invalid_argument& e) {
				cout << "playlist id " << inputWords[1] << " is not an integer." << std::endl;
				pint=false;
			}
			int pindex=findInP(allPlaylists, playlistid);
			if(pindex==-1){
				cout << "playlist " <<playlistid<< " does not exist" << endl;
			}
			else{
				allPlaylists.at(pindex)->setTitle(inputWords[2]);
				cout << "playlist " << playlistid << " name successfully changed to " << inputWords[2] << endl;
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
