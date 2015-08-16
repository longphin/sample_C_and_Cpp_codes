//Longphi Nguyen

#include "song.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

// NEEDS:
// where it says "remove this", remove those lines. Currently, the lines are being skipped. That is because when >> operator is called, we read another line ALONG with the line being read from the while condition.

using namespace std;


void searchSongs(vector<Songs> songs, string searchedfor, int searchmethod)
{
	vector<Songs> Found;

	// finding matches
	for(vector<Songs>::iterator itr=songs.begin(); itr!=songs.end(); itr++)
	{

		if((searchmethod==1 && itr->searchArtist(searchedfor)==true)
				|| (searchmethod==2 && itr->searchTitle(searchedfor)==true)
				|| (searchmethod==3 && itr->searchAlbum(searchedfor)==true
					|| (searchmethod==4 && itr->searchByPhrase(searchedfor)==true)))
		{
			Found.push_back(*itr);
		} // if
	} //for

	// sorting (if needed)
	if(Found.size()>1)
	{
		for(vector<Songs>::iterator itr=Found.begin(); itr!=Found.end(); itr++)
		{
			for(vector<Songs>::iterator itr2=Found.begin();itr2!=Found.end();itr2++)
			{
				if(((searchmethod==1 || searchmethod==3) && itr->getTitle()<itr2->getTitle())
						|| ((searchmethod==2 || searchmethod==4) && itr->getArtist()<itr2->getArtist()))
				{
					itr2->swapTitle(*itr);
				} // if need for swap
			} // for (sorting against)
		} // for (song to be possibly sorted)
	} // if

	// iterate through Found (now sorted) and display the info
	for(vector<Songs>::iterator itr=Found.begin();itr!=Found.end();itr++)
	{
		cout << *itr << endl;
	}
} //end searchArtist


int main()
{
	vector<Songs> songs;
	Songs song;
	char tmp[256];

	// READ SONGS
	//ifstream infm("songs.txt", ios::in);
	ifstream inf("songs.txt", ios::in);

	inf.getline(tmp,256); // remove this
	inf.ignore(); // remove this
	while(inf >> song)//infm.getline(tmp,256))
	{
		//inf >> song;
		song.getTitle();
		songs.push_back(song);

		inf.ignore();//infm.ignore();
	} // while reading lines

	//infm.close();
	inf.close();

	int choice;

	while(1) // infinite loop; exit when user inputs 0
	{
		// get user inputs
		cout << "Song Menu\n0. Done.\n1. Search for Artist.\n"
			<< "2. Search for Title.\n3. Search for Album.\n"
			<< "4. Search for title phrase.\n\n"
			<<	"Your choice: ";
		cin >> choice;
		cin.ignore();

		string searchfor;
		switch(choice)
		{
			case 0: // only exit possiblity
				return(0);
				break;
			case 1: 
				cout << "Please enter the artist's name: ";
				getline(cin, searchfor);

				searchSongs(songs, searchfor, 1);
				break;
			case 2:
				cout << "Please enter the title ";
				getline(cin, searchfor);

				searchSongs(songs, searchfor, 2);
				break;
			case 3:
				cout << "Please enter the album: ";
				getline(cin, searchfor);

				searchSongs(songs, searchfor, 3);
				break;
			case 4:
				cout << "Please enter the phrase: ";
				getline(cin, searchfor);

				searchSongs(songs, searchfor, 4);
				break;
			default:
				cout << "Your choice must be between 0 and 4.\n";
				break;
		} // switch

		cout << "\n";
	} // while

	return(0);
}

