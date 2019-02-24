/**
Author: Karanveer Singh
Class: CSCI 235
Assignment: Project 3
File: PlayList.h
Date: 10/16/2018

This file is the definition of the class PlayList which inherits from template class Linked Set. This class makes use of
a linked chain in order to store songs
*/

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include "LinkedSet.h"
#include"Song.h"

class PlayList : public LinkedSet <Song>
{

public:

  PlayList();                            // default constructor

  PlayList(Song& a_song);                // parameterized constructor

  PlayList(const PlayList& a_play_list); // copy constructor

  ~PlayList();                           //destructor


  /** adds a song to the PlayList from the end

  @pre new_song must not already be in the PlayList

  @post new_song is added to the PlayList

  @return true if new_song is added, false otherwise */

  bool add(Song& new_song);


  /** removes a_song from the PlayList while preserving the order of the PlayList

  @pre a_song must be present in the PlayList in order for it to be deleted

  @post a_song is removed from the PlayList and order of the PlayList is preserved

  @return true if song is removed, false otherwise */

  bool remove(Song& a_song);


  /** loops the PlayList*/

  void loop();


  /** unloops the PlayList */

  void unloop();


  /** displays the songs in the PlayList */

  void displayPlayList();

private:

  Node<Song>* tail_ptr_;           // pointer to last node


  /** @return a pointer that points to the last node in the PlayList */

  Node<Song>* getPointerToLastNode() const;


  /** @post previous_ptr is null if target is not in PlayList or if target is the

  first node, otherwise it points to the node preceding target

  @return: either a pointer to the node containing target

  or the null pointer if the target is not in the PlayList */

  Node<Song>* getPointerTo(const Song& target, Node<Song>*& previous_ptr) const;

};

#endif // end of PLAYLIST_H
