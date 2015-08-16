//Longphi Nguyen

#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "song.h"
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;


// used to convert string to lowercase, courtesy Sean on velocityreviews.com
int my_tolower(int c)
{
	return(tolower(c));
} // end my_tolower
int my_toupper(int c)
{
	return(toupper(c));
} // end my_toupper


// overloaded operators
ostream& operator<<(ostream &os, Songs &song)
{
	os << song.title << ":" << song.artist << ":" << song.album;
	return(os);
} // end << Songs

istream& operator>>(istream &is, Songs &song)
{
	string tmp;
	string title,artist,code,album;

  if(is.getline(tmp)){}else return(NULL);
//  is.getline(tmp, 256);
//	if(tmp) return(NULL);

	// get fields
	title=strtok(tmp, "___");
	is.ignore();
	artist=strtok(NULL, "___");
	is.ignore();
	code=strtok(NULL, "___");
	is.ignore();
	album=strtok(NULL, "___");
	is.ignore();

	// adjust format for title
	if(title.find("A ")==0) // found a match at start
	{
		title.erase(0,2);
		title+=", A";
	}else{
		if(title.find("THE ")==0) // found match at start
		{
			title.erase(0,4);
			title+=", THE";
		}
	}

	// adjust format name
	transform(artist.begin(),artist.end(),artist.begin(),my_tolower);
	// loop through and convert each first letter to capital
	transform(artist.begin(),artist.begin()+1,artist.begin(),my_toupper);
	for(string::size_type i=artist.find(" ", 0);
		i!=string::npos;
		i=artist.find(" ", i+1))
	{
		artist[i+1]=toupper(artist[i+1]); //note: need to change
		//transform(i,i,i+1,my_toupper); // doesnt work
		
	} //for

	// adjust format for album
	if(album.find(" CD+G",0)!=string::npos)
	{
		album.erase(album.find(" CD+G",0),5);
	} //if

//	cerr << title; cerr << " " << artist; cerr << " " << album << endl;

	song.title=title;
	song.artist=artist;
	song.album=album;
	return(is);
} // end >> Songs


bool Songs::searchArtist(string searchedartist) const
{
	if(artist==searchedartist)
		return(true);
	else
		return(false);
}


bool Songs::searchTitle(string searchedtitle) const
{
	if(title==searchedtitle)
		return(true);
	else
		return(false);
}

bool Songs::searchAlbum(string searchedalbum) const
{
	if(album==searchedalbum)
		return(true);
	else
		return(false);
}

bool Songs::searchByPhrase(string searchedphrase) const
{
	if(title.find(searchedphrase)!=string::npos)
		return(true);
	else
		return(false);
}

void Songs::swapTitle(Songs &rhs)
{
	title.swap(rhs.title);
	album.swap(rhs.album);
}


