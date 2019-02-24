/**

Author: Karanveer Singh

Class: CSCI 235

Instructor: Tiziana Ligorio

Assignment: Project 2


This is the header file for the Song class. This class sets the title, author, and album names for a song

*/


#ifndef SONG_H_
#define SONG_H_

#include <string>


class Song
{

public:

    Song(){} // default constructor


    /** @post title_ = title
    
    	author_ = author or "" if no author is provided
    	
    	album_ = album or "" if no album is provided
    */
    Song(const std::string& title, const std::string& author = "", const std::string& album = "");


    /** @post title_ = title */
    void setTitle(std::string title);  //"set" in setTitle here means "give a value" and has nothing

                                       // to do with the Set class. Similarly for setAuthor and setAlbum

    /** @post author_ = author */
    void setAuthor(std::string author);


    /** @post album_ = album */
    void setAlbum(std::string album);


    /** @return title_ */
    std::string getTitle() const;


    /** @return author_ */
    std::string getAuthor() const;


    /** @return album_ */
    std::string getAlbum() const;


	/** @return true if the title_, author_, and album_ of a song matches that of another,
				false if otherwise */
	friend bool operator== (const Song& lhs, const Song& rhs);


private:

    std::string title_;   

    std::string author_;

    std::string album_;
};

#endif // SONG_H
