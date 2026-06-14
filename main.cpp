#include <iostream>      //for cout and cin
#include <string>        //for string type
#include <stdexcept>     //for exception handling
#include <limits>        //for numeric_limits used in cin.ignore(), used for clearing the entire input buffer saafely
#include "SongKeeper.h"  //includes header file (Song and SongKeeper classes)

using namespace std;

int main(){

//creating SongKeeper object
    SongKeeper keeper;
    int choice;

//try to load saved songs when program starts
    try{
        keeper.loadFromFile("songs.txt"); 
    }
    catch(exception& e){ //exception handling prevents the prog from crashing if loading the file fails and prints the error mess to the user instead
        cout << "Error: " << e.what() << endl; //e.what() returns the actual error message text
    }

//main menu loop
    do{

        cout << "\n~~~~~~ SongKeeper Menu ~~~~~~" << endl;
    //main menu options
        cout << "1. Search a song." << endl;
        cout << "2. Add a song." << endl;
        cout << "3. Delete a song." << endl;
        cout << "4. Save to file." << endl;
        cout << "5. Exit." << endl;

    //user chooses option
        cout << "Choose: ";
        cin >> choice; //storing the option in choice

        while(cin.fail()){ //if input failed, invalid input entered

            cin.clear(); //removes the error state from cin so input can work again
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clears everything remaining in the input buffer until enter '\n'
            cout << "Invalid option. Please enter a number from 1 to 5: " << endl;
            cin >> choice; //asking the user again for valid input
        }

    //clears enter after valid input 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

    try{
        if(choice == 1) { //search a song

            int searchOption;
            string keyword;

            cout << "\nSearch by:" << endl;
        //search by menu
            cout << "1. Title." << endl;
            cout << "2. Artist." << endl;
            cout << "3. Album." << endl;
            cout << "4. Genre." << endl;
            cout << "5. Year." << endl;
            cout << "6. Back." << endl;

            cout << "Choose: ";
            cin >> searchOption;

            while(cin.fail()){

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please enter a number from 1 to 6: " << endl;
                cin >> searchOption;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

        //if user does not choose Back
            if(searchOption != 6) {

            //gets search text
                cout << "Enter search value: ";
                getline(cin, keyword);
                cout << endl;

            //calls search function
                keeper.searchSong(keyword, searchOption);
            }
        }

        else if(choice == 2) { //add a song

            string title, artist, album, genre;
            int year;

        //getting song information from user
            cout << "Enter title: ";
            getline(cin, title);

            cout << "Enter artist: ";
            getline(cin, artist);

            cout << "Enter album: ";
            getline(cin, album);

            cout << "Enter genre: ";
            getline(cin, genre);

            cout << "Enter year: ";
            cin >> year;

            while(cin.fail() || year < 0){ //if input failed, invalid input entered or negative

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid year. Please enter a (positive) number: " << endl;
                cin >> year;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

            Song song(title, artist, album, genre, year); //creates Song object

            keeper.addSong(song); //adds song into collection

        }

        else if(choice == 3) { //delete a song

            string title;

        //getting title from user
            cout << "Enter title of song to delete: ";
            getline(cin, title);
            cout << endl;

            keeper.deleteSong(title); //delete song from memory

            keeper.saveToFile("songs.txt"); //save updated collection to file

        }

        else if(choice == 4) { //save to file

            keeper.saveToFile("songs.txt"); //saves songs into text file

        }

        else if(choice == 5) { //exit program

            keeper.saveToFile("songs.txt"); //save before exiting

            cout << "Program stopped." << endl;
        }

        //invalid menu option
        else{

            cout << "Invalid option." << endl;
        }

    }
    
    catch(exception& e){ //prints error message instead of crashing the program

        cout << "Error: " << e.what() << endl;
    }
    }
//loop continues until user chooses Exit
    while (choice != 5);

    return 0;
}