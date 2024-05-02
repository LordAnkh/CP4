# CP4

apr 28
	discussed what we had done so far separately
	- playlist class (bst/heap) 
		implemented remove, find, insert, inorder traversal for show
		heap functions will be within the bst.
		playlist will have a root for the bst (null when it is a heap) and a vector for the heap (empty when it is a bst)
		the heap operations will work on the vector
		find, insert, inorder, percolates based on zybooks pseudo code
	- song class (node)
		
	- driver file
apr 30-1
	compiling and testing
	an early draft of the main menu file

	if(inputWords[0] == "song" && inputWords.size()>=5){
	add song to vector
	add song to bst
	add song to heap
	}
	else if(inputWords[0] == "remove" && inputWords.size()>=2){
		cout << "removing song " << inputWords[1] << endl;
		remove bst
		remove heap 
		set remove.
	}
	else if(inputWords[0] == "show_listen_time" && inputWords.size()==1){
		for vector
			if !remove
				song.show
	}
	else if(inputWords[0] == "favorite" && inputWords.size()==1){
		remove root from heap
		add favorite to vector
		output
	}
	else if(inputWords[0] == "listen" && inputWords.size()==3){
		getsong from bst
		change listen
		remove song from heap
		add song w new listen time
	}
	else if(input!= " "){
		cout << "Command not recognized, please try again." << endl;
		//inputWords.clear();
	}