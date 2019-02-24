/**
Author: Karanveer Singh
Class: CSCI 235
Assignment: Project 3
File: PlayList.cpp
Date: 10/16/2018

This file is the implementation of the class PlayList which inherits from template class Linked Set. This class makes use of
a linked chain in order to store songs
*/

#include "PlayList.h"
#include <iostream>

PlayList::PlayList() : tail_ptr_(nullptr)
{
} // end default constructor


PlayList::PlayList(Song& a_song)
{
  add(a_song);
} // end parameterized constructor


PlayList::PlayList(const PlayList& a_play_list) : LinkedSet(a_play_list), tail_ptr_(getPointerToLastNode())
{
} // end copy constructor


PlayList::~PlayList()
{
  unloop();
} // end of destructor


/** adds a song to the PlayList from the end

@pre new_song must not already be in the PlayList

@post new_song is added to the PlayList

@return true if new_song is added, false otherwise */

bool PlayList::add(Song& new_song)
{
  Node<Song>* new_node_ptr = new Node<Song>();
  new_node_ptr->setItem(new_song);   // the new node already points to nullptr through the constructor because we are
                                     // adding it to the end of the chain

  if(head_ptr_ == nullptr)           // if chain is empty
  {
    head_ptr_ = new_node_ptr;        // set head_ptr_ to the new node and
    tail_ptr_ = head_ptr_;           // since this node is the first in the
                                     // chain, the head and the tail pointer are the same
    item_count_++;

    return true;
  }
  else if(!contains(new_song))
  {
    tail_ptr_->setNext(new_node_ptr);  // link the new node to the chain
    tail_ptr_ = new_node_ptr;          // set the new node to tail_ptr_

    item_count_++;

    return true;
  }
  else
    return false;

} // end add


/** removes a_song from the PlayList while preserving the order of the PlayList

@pre a_song must be present in the PlayList in order for it to be deleted

@post a_song is removed from the PlayList and order of the PlayList is preserved

@return true if song is removed, false otherwise */

bool PlayList::remove(Song& a_song)
{
  Node<Song>* previous_ptr;      // points to node before the one we want to delete
  Node<Song>* node_to_delete_ptr = getPointerTo(a_song, previous_ptr);

  bool can_remove = !isEmpty() && (node_to_delete_ptr != nullptr);

  if(node_to_delete_ptr == head_ptr_)             // if the node_to_delete_ptr is the first node
  {
    Node<Song>* temp = node_to_delete_ptr;         // copy head_ptr_ into a temp pointer

    head_ptr_ = head_ptr_->getNext();              // set head_ptr_ as the next node

    // delete the node and return it to the system
    temp->setNext(nullptr);
    delete temp;
    temp = nullptr;

    item_count_ --;

    return true;
  }
  else if(can_remove)
  {
    previous_ptr->setNext(node_to_delete_ptr->getNext()); // point the previous_ptr to the node after the one we want to delete

    // return node to the system
    node_to_delete_ptr->setNext(nullptr);
    delete node_to_delete_ptr;
    node_to_delete_ptr = nullptr;

    item_count_ --;
  }

  return can_remove;
} // end remove


/** loops the PlayList */

void PlayList::loop()
{
  tail_ptr_->setNext(head_ptr_);
} // end loop


/** unloops the PlayList */

void PlayList::unloop()
{
  tail_ptr_->setNext(nullptr);
} // end unloop


/** @return a pointer that points to the last node in the PlayList */

Node<Song>* PlayList::getPointerToLastNode() const
{
  Node<Song>* pointer_to_last_node;

  if(head_ptr_ == nullptr)                // if the chain is empty
    pointer_to_last_node = nullptr;
  else
  {
    Node<Song>* cur_ptr = head_ptr_;      // create a chain pointer to traverse the chain
    while(cur_ptr != nullptr)
    {
      if(cur_ptr->getNext() == nullptr)   // if the next node is nullptr
        pointer_to_last_node = cur_ptr;

      cur_ptr = cur_ptr->getNext();       // Advance the chain pointer
    }
  }

  return pointer_to_last_node;

} // end getPointerToLastNode


/** @post previous_ptr is null if target is not in PlayList or if target is the

first node, otherwise it points to the node preceding target

@return: either a pointer to the node containing target

or the null pointer if the target is not in the PlayList */

Node<Song>* PlayList::getPointerTo(const Song& target, Node<Song>*& previous_ptr) const
{
  previous_ptr = nullptr;
  Node<Song>* pointer_to_return;

  if(target == head_ptr_->getItem())
    pointer_to_return =  head_ptr_;

  else
  {
    bool found = false;
    previous_ptr = head_ptr_;
    Node<Song>* cur_ptr = head_ptr_->getNext();      // since the head_ptr_ has already been checked
                                                     // cur_ptr is set to the next node

    while(!found && cur_ptr != nullptr)
    {
      if(cur_ptr->getItem() == target)
      {
        found = true;
        pointer_to_return = cur_ptr;
      }
      else
      {
        cur_ptr = cur_ptr->getNext();                 // advance cur_ptr
        previous_ptr = previous_ptr->getNext();       // advance previous_ptr
      }
    }
  }

  return pointer_to_return;

} // end getPointerTo


/** displays the songs in the PlayList */

void PlayList::displayPlayList()
{
  std::vector<Song> chain_vector = toVector();        // put all of the songs from the linked chain into a vector

  for(int i = 0; i < item_count_; i++)
  {
    std::cout << "* Title: " << chain_vector.at(i).getTitle();

    std::cout << " * Author: " << chain_vector.at(i).getAuthor();

    std::cout << " * Album: " << chain_vector.at(i).getAlbum() << " * " << std::endl;
  }

  std::cout << "End of playlist\n";

} // end displayPlayList
