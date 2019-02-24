/**

Author: Karanveer Singh

Class: CSCI 235

Instructor: Tiziana Ligorio

Assignment: Project 2


This is the header file for the class PlayList. This class uses the help of the class Set in

order to put songs into a playlist

*/

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "Set.h"
#include "Song.h"
#include <vector>


class PlayList
{

public:

    PlayList() {}// default constructor

    
    PlayList(const Song& a_song);

    
    /** @return the number of songs in playlist_ */
    
    int getNumberOfSongs() const;

    
    /** @return true if playlist_ is empty, false otherwise */
    
    bool isEmpty() const;

    
    /** @return true if song is added to playlist_, false if otherwise
    
    @post adds song to playlist_ */
    
    bool addSong(const Song& new_song);

    
    /** @return true if song is removed from playlist_, false if otherwise
    	
    @post removes song from playlist_ */
    
    bool removeSong(const Song& a_song);

    
    /** @post playlist.item_count_ = 0 */
    
    void clearPlayList();
    
	
	/** Uses the toVector method from class Set
	@post displays the title, author, and album names for each
	of the songs in playlist_ */
	
    void displayPlayList() const;


private:

    Set<Song> playlist_;    // playlist_ is a Set of type Song
};

#endif // PLAYLIST_H
