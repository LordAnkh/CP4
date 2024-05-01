#include <iostream>
#include <stdlib.h>
#include "Playlist.h"
using namespace std;

Playlist::Playlist(){
	root=nullptr;
}
// Destructor
Playlist::~Playlist() {
   del(root);
}
void Playlist::del(Song* song) {
    if (song != nullptr) {
        clear(song->left);
        clear(song->right);
        delete song;
    }
}
Song* Playlist::getSong(String title){
	Song*curr=root;
	while(curr!=nullptr){
		if(title==curr.title){
			return curr;
		}
		else if(title<curr->key){
			curr=curr->left;
		}
		else{
			curr=curr->right;
		}
	}
	return nullptr;
}
void Playlist::insert(Song song){
	if(root==nullptr){
		root=song;
	}
	else{
		Song*current=root;
		while(current!=nullptr){
			if(song.title<current.title){
				if(current->left==nullptr){
					current->left=song;
					current=nullptr;
				}else{
					current=current->left;	
				}
			}
			else{
				if(current->right==nullptr){
					current->right=node;
					current=nullptr;
				}else{
					current=current->right;
				}
			}
		}
	}
}
void Playlist::remove(Song song){
	song par=nullptr; //parent
	song curr=root;
	while(curr!=nullptr){ //search
		if(curr.title==song.title){ //found
			if(curr->left==nullptr && curr->right==nullptr){//if node is leaf
				if(par==nullptr){ //root
					root=nullptr;
				}
				else if(par->left==curr)
					par->left=nullptr;
				else if(par->right==curr)
					par->right=nullptr;
			}
			else if(curr->right==nullptr){//w left child
				if(par==nullptr){
					root=curr->left;
				}
				else if(par->left==curr)
					par->left=cur->left;
				else
					par->right=cur->left;
			}
			else if(curr->left==nullptr){//w right child
				if(par==nullptr){
					root=curr->right;
				}
				else if(par->right==curr)
					par->right=cur->right;
				else
					par->left=cur->right;
			}
			else{//two children
				Song*suc=curr->right;
				while(suc->left!=nullptr){
					suc=suc->left;
				}
				string successordata=suc.title;
				remove(suc);
				curr.title=successordata;
			}
		}
		else if (curr.title<song.title){
			par=curr;
			curr=curr->right;
		}else{
			par=curr;
			curr=curr->left;
		}
	}
}
void Playlist::heapify(){
	
}
void Playlist::percUp(int i){
	int parenti=0;
	while(i>0){
		parenti=(i-1/2);
		if(heap[i]<=heap[parenti]){
			heap[i].heapIndex=i;
			return;
		}else{
			Song temp=heap[i];
			heap[i]=heap[parenti];
			heap[parenti]=temp;
			i=parenti;
		}
	}
}
void Playlist::insertHeap(Song song){
	heap.push_back(song);
	percUp(song);
}
void Playlist::percDown(int i){
	int childi=2*i+1;
	Song value=heap[i];
	while(childi<heap.size()){
		int max=value.Time();
		int maxi=-1;
		for(i=0;i<2&&i+childi<heap.size();++i){
			if(heap[i+childi]->maxValue){
				max=heap[i+childi].Time();
				maxi=i+childi;
			}
		}
		if(max==value.Time()){
			heap[i].heapIndex=i;
			return;
		}
		else{
			Song temp=heap[i];
			heap[i]=heap[maxi];
			heap[maxi]=temp;
			i=maxi;
			childi=2*i+1;
		}
	}
}
void Playlist::show(Song*rootInput){ //always input the tree's root to start recursive
	if(rootInput==null){
		return;
	}
	show(rootInput->left);
	rootInput.show();
	show(rootInput->right);
}
