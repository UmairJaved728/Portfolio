#include <iostream>
#include <fstream>
#include "Song.h"
#include "HashTable.h"

using namespace std;

int printMenu();

int main()
{
    int option, duration;
    fstream inputFile, outputFile;
    string filename, title, artist;
    bool valid;
    // Data structure used is : Hash Table with TombStoning and Linear Probation as a Collision Resolution Technique
    HashTable *table = new HashTable;
    Song *song;

    do{     // loop until user exits
        option = printMenu();       // constant time O(1)

        if(option == 1)
        {
            cout << "\t    <---  LOADING TRACKS  --->\n";
            valid = false;
            do{
                cout << "\nEnter the File Name from where you want to load: ";
                cin >> filename;

                inputFile.open(filename, ios::in);

                if(inputFile.fail())
                    cout << "\nOOPS! File cannot be opened or does not exist. Try Again...\n";
                else
                    valid = true;
            } while( !valid );

            cout << "\nFile Opened. Starting to Read the File.\n";
            while( !inputFile.eof() )       // Complexity : O(n) where n is the number of lines in the file
            {
                getline(inputFile, title, '\t');
                getline(inputFile, artist, '\t');
                inputFile >> duration;
                inputFile.ignore();

                song = new Song(title, artist, duration);
                table->insert(song);            // O( M ) where M = the length of the string (artist/band name)
                                                // Rest of the Insert Function is Constant time O(1)
            }
            inputFile.close();
            cout << "\nData has been Read and Loaded. Closing the File...\n";
        }       // Total Complexity -> O( nM )

        else if ( option == 2 )
        {
            cout << "\t    <---  SAVING TRACKS  --->\n";
            valid = false;

            if(table->getOccupied() == 0) {
                cout << "\nOOPS! No Data is Loaded So far in the Library. Please Load the Data before Saving.\n";
            } else {
                do {
                    cout << "\nEnter the File Name where you want to Save the Library: ";
                    cin >> filename;

                    outputFile.open(filename, ios::out);

                    if (outputFile.fail())
                        cout << "\nOOPS! File cannot be opened or Permission Denied. Try Again...\n";
                    else
                        valid = true;
                } while (!valid);

                cout << "\nFile Opened. Starting to write the File.\n";

                table->writeToFile(outputFile);     // Complexity -> O( n ) where n is the total number of records
                outputFile.close();

                cout << "\nData has been Written and Saved. Closing the File...\n";
            }
        }

        else if(option == 3)
        {
            cout << "\t    <---  SEARCHING TRACKS  --->\n";
            if(table->getOccupied() == 0) {
                cout << "\nOOPS! No Data is Loaded So far in the Library. Please Load the Data before Saving.\n";
            } else {
                cout << "\nEnter the Artist / Band Name, you want to Search: ";
                getline(cin, artist);

                table->printSong(artist);       // Complexity -> O( m ) where m is the length of string artist/band name
                                                    // Rest of the Searching and printing is constant
            }
        }

        else if( option == 4 )
        {
            cout << "\t    <---  DELETING TRACKS  --->\n";
            if(table->getOccupied() == 0) {
                cout << "\nOOPS! No Data is Loaded So far in the Library. Please Load the Data before Saving.\n";
            } else {
                cout << "\nEnter the Artist / Band Name, you want to Remove Song: ";
                getline(cin, artist);

                valid = table->remove(artist);      // Complexity -> O( m ) where m is the length of string artist/band name
                // Rest of the Searching and printing is constant

                if (!valid) {
                    cout << "OOPS!! The Artist / Band Name does not exist.\n";
                } else {
                    cout << "\n\t<---  RESULT  --->\n\n";
                    cout << artist << "'s Song Successfully Removed from the Library.\n";
                }
            }
        }

    } while (option != 0);

    delete table;
    cout << "Thank You For Using The Application. GOOD BYE.\n\n";
    return 0;
}

int printMenu()
{
    int option;

    do{
        cout << "\n  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n\n";
        cout << "\tEnter <-- 1 --> To Load All Tracks From File.\n";
        cout << "\tEnter <-- 2 --> Save Tracks From Library To File.\n";
        cout << "\tEnter <-- 3 --> Search Track By Artist/Band Name.\n";
        cout << "\tEnter <-- 4 --> Remove Specific Track(s).\n";
        cout << "\tEnter <-- 0 --> To Exit The Program.\n";
        cout << "\n  <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n\n";
        cout << "\t\tEnter Your Choice: ";
        cin >> option;

        if(cin.fail() || option < 0 || option > 4)
        {
            cin.clear();
            cin.ignore();
            cout << "\nOOPS! It's an Invalid Input. Try Again...\n";
            option = -1;
        }
    } while(option < 0 || option > 4);
    cin.ignore();
    cout << "\n";

    return option;
}