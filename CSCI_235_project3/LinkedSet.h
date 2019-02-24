//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
//  Modified by Tiziana Ligorio 2018

/** ADT set: Link-based implementation.
    @file LinkedSet.h */


#ifndef LINKED_SET_
#define LINKED_SET_

#include "SetInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedSet : public SetInterface<ItemType>
{
protected:
   Node<ItemType>* head_ptr_; // Pointer to first node
   int item_count_;           // Current count of set items
    
   // Returns either a pointer to the node containing a target
   // or the null pointer if the target is not in the set.
   Node<ItemType>* getPointerTo(const ItemType& target) const;
   
public:
   LinkedSet();                                 // Default constructor
   LinkedSet(const LinkedSet<ItemType>& a_set); // Copy constructor
   virtual ~LinkedSet();                        // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const ItemType& new_entry);
   bool remove(const ItemType& an_entry);
   void clear();
   bool contains(const ItemType& an_entry) const;
   std::vector<ItemType> toVector() const;
}; // end LinkedSet

#include "LinkedSet.cpp"
#endif /*LINKED_SET_*/
