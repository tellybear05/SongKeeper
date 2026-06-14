//to prevent the header from being included multiple times:
#ifndef SONGKEEPER_H
#define SONGKEEPER_H

#include <string>

//a class for managing 1 song
class Song{
//creating the data members of the class Song
private:
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int year;

public:
//default constructor, to initialize variables safely
    Song();
//parameterized constructor, to create a song with its data
    Song(std::string title, std::string artist, std::string album, std::string genre, int year);

//these variables are private, so we need to call them like this to read from the private class    
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    int getYear() const;

//function for printing the song info
    void print() const;
};

//a class to manage all songs
class SongKeeper{
private:

    Song** songs; //dynamic array of song pointers
    int size; //current number of songs
    int capacity; //max space currently availabe

//in case of the array becomes full, we create a bigger array:
    void resize();
//deletes all songs from dynamic memory
    void clear();

//converts text to lowercase for case-insensitive comparison
    std::string toLower(std::string text) const;

public:
//constructor, creating empty collection
    SongKeeper();
//deconstructor, to clean the memory when object dies
    ~SongKeeper();

//function declerations, which functions exist
    void addSong(const Song& song); //adds a new song to the collection
    void searchSong(std::string keyword, int option) const; //searches for a song by title, artist, album, genre, or year
    void deleteSong(std::string title); //deleting a song from the collection using its title
    void saveToFile(std::string filename) const; //saving all songs from the collection into a text file
    void loadFromFile(std::string filename); //loading songs from a text file into the program
};

//closing the include guard
#endif