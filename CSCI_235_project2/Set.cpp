/**

Author: Karanveer Singh

Class: CSCI 235

Instructor: Tiziana Ligorio

Assignment: Project 2


This is the implementation file for the class Set

*/

#include "Set.h"


template<class ItemType>
Set<ItemType>::Set()
{
	item_count_ = 0;                  // initialize item_count_ to 0
	
	max_items_ = DEFAULT_SET_SIZE;    // initialize max_items_ to DEFAULT_SET_SIZE
}


template<class ItemType>
int Set<ItemType>::getCurrentSize() const
{
    return item_count_;
}


template<class ItemType>
bool Set<ItemType>::isEmpty() const
{
    return (item_count_ == 0);
}


template<class ItemType>
bool Set<ItemType>::add(const ItemType& newEntry)
{
    bool has_space_to_add = (item_count_ < max_items_);       // true if there is space in items_

    bool not_already_in_set = (getIndexOf(newEntry) == -1);   // true if newEntry is not already in items_

    if(has_space_to_add && not_already_in_set)
    {
        items_[item_count_] = newEntry;                       // add newEntry to items_

        item_count_++;
    }

    return has_space_to_add;
}


template<class ItemType>
bool Set<ItemType>::remove(const ItemType& anEntry)
{
    int index = getIndexOf(anEntry);

    bool can_remove = (!isEmpty() && index > -1);       // true if anEntry is in items_ and items_ is not empty

    if(can_remove)
    {
        item_count_--;                                   

        items_[index] = items_[item_count_];            // replace the entry with the last item in items_
    }

    return can_remove;
}


template<class ItemType>
void Set<ItemType>::clear()
{
    item_count_ = 0;
}


template<class ItemType>
bool Set<ItemType>::contains(const ItemType& anEntry) const
{
    return (getIndexOf(anEntry) > -1);
}


template<class ItemType>
std::vector<ItemType> Set<ItemType>::toVector() const
{
    std::vector<ItemType> item_set;

    for(int i = 0; i < item_count_; i++)
    {
        item_set.push_back(items_[i]);                // copy items_ into the vector item_set
    }

    return item_set;
}


template<class ItemType>
int Set<ItemType>::getIndexOf(const ItemType& target) const
{
    int index = -1;

    for(int i = 0; i < item_count_; i++)
    {
        if(items_[i] == target)  
        {
            index = i;
        }
    }

    return index;
}
