#include "SongKeeper.h"   //includes the header file
#include <iostream>       //for cout and cin
#include <fstream>        //for file handling
#include <sstream>      // for reading seperated text and converting year
#include <stdexcept>    //for error handling with exceptions
#include <cctype>       //for using tolower() converting to lowercase
#include <limits>       //for numeric_limits used in cin.ignore(), used for clearing the entire input buffer saafely

using namespace std;

//default constructor,for creating an empty song object for dynamic array
Song::Song(){
    title = "";
    artist = "";
    album = "";
    genre = "";
    year = 0;
}

//constructor with parameters, creates a song with info entered by the user
Song::Song(string title, string artist, string album, string genre, int year){

//is year is invalid then throw an error
    if(year<0){
        throw invalid_argument("Year cannot be negative.");
    }

//this-> is used bc the parameter names are the same as the class variable names
//works: putting the parameter ttle into the object's title
    this->title = title;
    this->artist = artist;
    this->album = album;
    this->genre = genre;
    this->year = year;
}

//getter for title from the private class
string Song::getTitle() const{
    return title;
}

//getter for artist from the private class
string Song::getArtist() const{
    return artist;
}

//getter for album from the private class
string Song::getAlbum() const{
    return album;
}

//getter for genre from the private class
string Song::getGenre() const{
    return genre;
}

//getter for year from the private class
int Song::getYear() const{
    return year;
}

//prints one song with all information
void Song::print() const{

    cout << "Title: " << title << endl;
    cout << "Artist: " << artist << endl;
    cout << "Album: " << album << endl;
    cout << "Genre: " << genre << endl;
    cout << "Year: " << year << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

//SongKeeper constructor, creates empty dynamic array collection for songs
SongKeeper::SongKeeper(){

    size = 0;       //current number of songs are stored
    capacity = 2;   //starting array size, how many spaces available

//dynamic array of SOng pointers
    songs = new Song*[capacity];
}

//destructor, frees dynamic memory when program ends
SongKeeper::~SongKeeper(){
//delete all Song objects
    clear();
//delete the array of pointers
    delete[] songs;
}

//clean function, deletes all songs from memory
void SongKeeper::clear(){
    
    for(int i = 0; i < size; i++){ //loop for deleting the song
        delete songs[i];
    }
    size = 0;
}

//resize function, makes array bigger when full
void SongKeeper::resize(){

    capacity = capacity * 2; //double the capacity, making it better
    Song** newSongs = new Song*[capacity]; //create new bigger array of Song pointers

    for(int i = 0; i < size; i++) { //copy old songs (pointers) into new array
        newSongs[i] = songs[i];
    }

    delete[] songs; //deletes old pointer, array only
    songs = newSongs; //point to new bigger array
}

string SongKeeper::toLower(string text) const{
    for(int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }

    return text;
}

//adds a new song into the collection
void SongKeeper::addSong(const Song& song){

    for(int i = 0; i < size; i++){ //check if song already exists
        //comparing title and artist for checking duplicates and case-insensitive
        if(toLower(songs[i]->getTitle()) == toLower(song.getTitle()) &&
           toLower(songs[i]->getArtist()) == toLower(song.getArtist())){

            throw runtime_error("Song already exists.");
        }
    }
    
    if(size == capacity) {  //if array is full -> resize (make it bigger)
        resize();
    }

    songs[size] = new Song(song);  //create a new dynamic Song object

    size++;  //increase number of songs

    cout << "Song added." << endl;
}

//searches for a song
void SongKeeper::searchSong(string keyword, int option) const {

//check if collection is empty
    if(size == 0) {

        throw runtime_error("No song in the collection, please add a song first.");
    }

    bool found = false; //no matching song found yet (found=0)
    string key = toLower(keyword); //converting to lower for making it case insesitive

//go and checks through all songs (case-insensitive)
    for(int i = 0; i < size; i++) {
    
        if(option == 1 && toLower(songs[i]->getTitle()) == key) { //search by title

            songs[i]->print();
            found = true;
        }

        else if(option == 2 && toLower(songs[i]->getArtist()) == key) { //search by artist

            songs[i]->print();
            found = true;
        }

        else if(option == 3 && toLower(songs[i]->getAlbum()) == key) { //search by album

            songs[i]->print();
            found = true;
        }

        else if(option == 4 && toLower(songs[i]->getGenre()) == key) { // Search by genre


            songs[i]->print();
            found = true;
        }

        else if(option == 5) { //search by year

            int yearNum;

            stringstream ss(keyword); //converting keyword text into integer year
            ss >> yearNum;

            if(songs[i]->getYear() == yearNum){

                songs[i]->print();
                found = true;
            }
        }
    }

//if no match was found
    if(!found) {

        cout << "No matching song found." << endl;
    }
}

//deletes a song by title
void SongKeeper::deleteSong(string title) {

    if(size == 0){ //if collection is empty then throw error
        throw runtime_error("No songs in the collection.");
    }

    int found = 0; //count how many songs match the title

//show all matching songs in the collection
    for(int i = 0; i < size; i++){

        if(toLower(songs[i]->getTitle()) == toLower(title)){ //case insensitive comparison
        //print matching songs to the user
            cout << found + 1 << ". "
                 << songs[i]->getTitle() << " - "
                 << songs[i]->getArtist() << endl;

            found++; //count how many matches were found
        }
    }

    if(found == 0){ //if no match found then throw error

        throw runtime_error("Song was not found.");
    }

    int choice; //stores which song user wants to delete

    if(found > 1){ //if more than one song found then ask the user which one to delete or go back

        cout << "0. Back" << endl;
        cout << "Choose song number to delete: ";
        cin >> choice;

        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number: ";
            cin >> choice;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(choice == 0){
            cout << "Delete cancelled." << endl;
            return;
        }

        if(choice < 1 || choice > found){
            throw runtime_error("Invalid delete choice.");
        }
    }
    else{ //if one song was found then immeditely delete without asking the user
        choice = 1;
    }

    int current = 0; //tracks the current matching song number during sec loop

    for(int i = 0; i < size; i++){ //go through the songs list again

        if(toLower(songs[i]->getTitle()) == toLower(title)){ //check matching titles again

            current++; //increasing the current match count

            if(current == choice){ //if the correct song was chosen from the user then delete it

                delete songs[i]; //frees dynamic memory of that song

                for(int j = i; j < size - 1; j++){ //shifting remianing songs to left to fill empty gap
                    songs[j] = songs[j + 1];
                }

                size--; //reduce size

                cout << "Song deleted." << endl;
                return;
            }
        }
    }
}

//saves all songs into a text file
void SongKeeper::saveToFile(string filename) const{

    ofstream file(filename); //open file for writing

    if(!file) { //check if file cannot open then throw error

        throw runtime_error("File could not be open for saving.");
    }

    for(int i = 0; i < size; i++) { //write every song in one line

        file << songs[i]->getTitle() << ";"
             << songs[i]->getArtist() << ";"
             << songs[i]->getAlbum() << ";"
             << songs[i]->getGenre() << ";"
             << songs[i]->getYear() << endl;
    }

    file.close(); //closing file

    cout << "songs.txt file is updated." << endl;
}

//loads songs from text file
void SongKeeper::loadFromFile(string filename){

    ifstream file(filename); //open file for reading

    if(!file){ //if file does not exist yet, continue normally

        cout << "No saved file found." << endl;
        return;
    }

    clear(); //remove old songs before loading

    string line;

    while(getline(file, line)){ //readong file line by line
        
        string title, artist, album, genre, yearText;
        int year;

        stringstream ss(line); //stringstream for splitting the line by semicolon

        getline(ss, title, ';');
        getline(ss, artist, ';');
        getline(ss, album, ';');
        getline(ss, genre, ';');
        getline(ss, yearText);

        stringstream yearStream(yearText); //converting year text into integer
        yearStream >> year;

        Song song(title, artist, album, genre, year); //creating song from loaded data

        if(size == capacity){
            resize();
        }

        songs[size] = new Song(song);
        size++; 
    }

    file.close(); //closing file

    cout << "Songs loaded from file." << endl;
}