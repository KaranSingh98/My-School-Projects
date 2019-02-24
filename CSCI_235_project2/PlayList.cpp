/**

Author: Karanveer Singh

Class: CSCI 235

Instructor: Tiziana Ligorio

Assignment: Project 2


This is the implementation file for the class PlayList. The methods in this class use methods from the class Set

to accomplish its task of putting songs into a playlist.

*/

#include "PlayList.h"
#include <iostream>


PlayList::PlayList(const Song& a_song)
{
    playlist_.add(a_song);            // adds a_song to playlist_
}


int PlayList::getNumberOfSongs() const
{
    return playlist_.getCurrentSize();   // returns the number of songs in playlist_
}


bool PlayList::isEmpty() const
{
    return playlist_.isEmpty();      // checks to see if playlist_ is empty
}


bool PlayList::addSong(const Song& new_song)
{
    return playlist_.add(new_song);    // adds new_song to playlist_
}


bool PlayList::removeSong(const Song& a_song)
{
    return playlist_.remove(a_song);   // removes a_song from playlist_
}


void PlayList::clearPlayList()
{
    playlist_.clear();                 // clears the songs in playlist_
}


void PlayList::displayPlayList() const
{
	std::vector<Song> playlist_of_songs = playlist_.toVector();  // puts the songs from playlist_ into a vector
	
   for(int i = 0; i < getNumberOfSongs(); i++)
    {
        std::cout << "* Title: " << playlist_of_songs.at(i).getTitle();
      
        std::cout << " * Author: " << playlist_of_songs.at(i).getAuthor();

        std::cout << " * Album: " << playlist_of_songs.at(i).getAlbum() << " * " << std::endl;
    }

    std::cout << "End of playlist\n";
}
