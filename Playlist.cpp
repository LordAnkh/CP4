#include <iostream>
#include <stdlib.h>
#include "Playlist.h"
using namespace std;

Playlist::Playlist(){
	root=nullptr;
}
// Destructor
Playlist::~Playlist() {
   clear(root);
}
void Playlist::clear(Song* song) {
    if (song != nullptr) {
        clear(song->left);
        clear(song->right);
        delete song;
    }
}
Song* Playlist::getSong(string title){
	Song*curr=root;
	while(curr!=nullptr){
		if(title==curr->Title()){
			return curr;
		}
		else if(title<curr->Title()){
			curr=curr->left;
		}
		else{
			curr=curr->right;
		}
	}
	return nullptr;
}
void Playlist::insert(Song* song){
	if(root==nullptr){
		root=song;
		//cout<<"check root"<<endl;
	}
	else{
		Song*current=root;
		while(current!=nullptr){
			//cout<<"check start"<<endl;
			if(song->Title()<current->Title()){
				//cout<<"check second"<<endl;
				if(current->left==nullptr){
					//cout<<"check left"<<endl;
					current->left=song;
					//current=nullptr;
					break;
				}else{
					current=current->left;	
				}

			}
			else{
				if(current->right==nullptr){
					//cout<<"check right"<<endl;
					current->right=song;
					//current=nullptr;
					break;
				}else{
					current=current->right;
				}
			}
		}
	}
}
void Playlist::remove(Song song){
	Song* par=nullptr; //parent
	Song* curr=root;
	while(curr!=nullptr){ //search
		if(curr->Title()==song.Title()){ //found
			if(curr->left==nullptr && curr->right==nullptr){//if node is leaf
				//cout<<0<<endl;
				if(par==nullptr){ //root
					root=nullptr;
				}
				else if(par->left==curr)
					par->left=nullptr;
				else if(par->right==curr)
					par->right=nullptr;
				return;
			}
			else if(curr->right==nullptr){//w left child
				//cout<<'l'<<endl;
				if(par==nullptr){
					root=curr->left;
				}
				else if(par->left==curr)
					par->left=curr->left;
				else
					par->right=curr->left;
				return;
			}
			else if(curr->left==nullptr){//w right child
				//cout<<'r'<<endl;
				if(par==nullptr){
					root=curr->right;
				}
				else if(par->right==curr)
					par->right=curr->right;
				else
					par->left=curr->right;
				return;
			}
			else{//two children
				//cout<<2<<endl;
				Song* sucParent = curr;
				Song* suc = curr->right;

				while (suc->left != nullptr) {
					sucParent = suc;
					suc = suc->left;
				}

				// Replace curr's Title with successor's Title
				curr->setTitle(suc->Title());

				// Handle removal of successor node
				if (sucParent->left == suc) {
					sucParent->left = suc->right;
				} else {
					sucParent->right = suc->right;
				}

				return;
			}
		}
		else if (curr->Title()<song.Title()){
			par=curr;
			curr=curr->right;
		}else{
			par=curr;
			curr=curr->left;
		}
	}
}

int Playlist::percUp(int i){
	while (i > 0) {
		//cout<<"index get "<<i<<endl;
		int parenti = (i - 1) / 2; // Calculate the parent index
		// If the current node is not greater than its parent, stop percolating
		//cout<<heap.size()<<endl;
		//cout<<i<<":curr "<<heap[i]->Title()<<endl;
		//cout<<parenti<<":parent "<<heap[parenti]->Title()<<endl;
		if (heap[i]->Time() <= heap[parenti]->Time()) {
			heap[i]->heapIndex = i;
			heap[parenti]->heapIndex = parenti;
			return heap[i]->heapIndex; // Exit the loop as the heap property is satisfied
		}else{
			Song* temp=heap[i];
			heap[i]=heap[parenti];
			heap[parenti]=temp;
			heap[i]->heapIndex = i;
			heap[parenti]->heapIndex = parenti;

			i = parenti;
		}
    }
	return 0;
}
void Playlist::insertHeap(Song& song){
	heap.push_back(&song);
	song.heapIndex=heap.size()-1;
	int newIndex=percUp(song.heapIndex);
   song.heapIndex = newIndex;
	//cout<<"index get "<<song.heapIndex<<endl;
}
int Playlist::percDown(int i){
	int childi=2*i+1;
	Song* value=heap[i];
	while(childi<heap.size()){
		int max=value->Time();
		int maxi=i;
		for(int j=0;j<2&&j+childi<heap.size();++j){
			if(heap[j+childi]->Time()>=max){
				max=heap[j+childi]->Time();
				maxi=j+childi;	
			}
		}
		if(max==value->Time()){
			heap[i]->heapIndex=i;
			heap[maxi]->heapIndex=maxi;
			return heap[i]->heapIndex;
			//cout<<"percd add heap "<<heap[i].heapIndex<<endl;
		}
		else{
			Song* temp=heap[i];
			heap[i]=heap[maxi];
			heap[maxi]=temp;
			i=maxi;
			childi=2*i+1;
		}
	}
	return 0;
}
void Playlist::heapRemove(int i) {
   /*if (i < 0 || i >= heap.size()) {
		return;
	}
	heap.erase(heap.begin()+i);
	for(int j=i;j<heap.size();j++){
		heap[j]->heapIndex=j;
	}*/
	if (i < 0 || i >= heap.size()) {
        return;
    }
	//cout<<"check"<<endl;
	//cout<<"tbr "<<i<<endl;
	heap[i] = heap.back();
	heap[i]->heapIndex = i;
	heap.pop_back();
	if(i==heap.size()){
		i--;
	}
	
	if (heap.empty()) {
		return; // If the heap is empty after removal
	}
	if (i > 0 && heap[i]->Time() < heap[(i - 1) / 2]->Time()) {
		//cout<<1<<endl;
		percDown(i);
	} else if(i>0 && heap[i]->Time() > heap[(i - 1) / 2]->Time()){	
		//cout<<2<<endl;
		percUp(i);
	}else if (i==0&&heap.size()>1&&heap[i+1]->Time()>heap[i]->Time()){
		//cout<<3<<endl;
		percDown(i);
	}
	else if (i==0&&heap.size()>=3&&heap[i+2]->Time()>heap[i]->Time()){
		//cout<<4<<endl;
		int childi=2*i+2;
		for(childi;childi<heap.size() && heap[childi]->Time()>heap[i]->Time();childi=childi*2+1){
			Song*temp=heap[i];
			heap[i]=heap[childi];
			heap[childi]=temp;
			i=childi;
		}
		
	}
	/*for(int i=0;i<heap.size();i++){
		cout<<heap[i]->Title()<<":"<<heap[i]->heapIndex<<" ";
	}
	cout<<endl;*/
}
void Playlist::show(Song*rootInput){ //always input the tree's root to start recursive
	if(rootInput==nullptr){
		return;
	}
	show(rootInput->left);
	rootInput->show();
	show(rootInput->right);
}