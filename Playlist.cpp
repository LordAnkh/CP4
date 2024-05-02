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
				cout<<0<<endl;
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
				cout<<'l'<<endl;
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
				cout<<'r'<<endl;
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
				cout<<2<<endl;
				Song*suc=curr->right;
				while(suc->left!=nullptr){
					suc=suc->left;
				}
				/*string successordata=suc->Title();
				remove(*suc);
				curr->Title()=successordata;*/
				curr->setTitle(suc->Title());
                // Remove successor node
                remove(*suc);
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

void Playlist::percUp(int i){
	int parenti=0;
	while(i>=0){
		parenti=(i-1)/2;
		if(heap[i].Time()<=heap[parenti].Time()){
			heap[i].heapIndex=i;
			return;
		}else{
			std::swap(heap[i], heap[parenti]);
			i=parenti;
		}
	}
}
void Playlist::insertHeap(Song& song){
	heap.push_back(song);
	song.heapIndex=heap.size()-1;
	percUp(song.heapIndex);
}
void Playlist::percDown(int i){
	int childi=2*i+1;
	Song value=heap[i];
	while(childi<heap.size()){
		int max=value.Time();
		int maxi=-1;
		for(i=0;i<2&&i+childi<heap.size();++i){
			if(heap[i+childi].Time()>=max){
				max=heap[i+childi].Time();
				maxi=i+childi;
			}
		}
		if(max==value.Time()){
			heap[i].heapIndex=i;
			cout<<"percd add heap "<<heap[i].heapIndex<<endl;
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
void Playlist::heapRemove(int i) {
   if (i < 0 || i >= heap.size()) {
		return;
	}
	heap[i] = heap[heap.size()];
	heap[i].heapIndex=-1;
	heap.pop_back();
	if (i == 0 || heap[i].Id() <= heap[(i/2-1)].Id()) {
		percDown(i);
	} else {
		percUp(i);
	}
}
void Playlist::show(Song*rootInput){ //always input the tree's root to start recursive
	if(rootInput==nullptr){
		return;
	}
	show(rootInput->left);
	rootInput->show();
	show(rootInput->right);
}