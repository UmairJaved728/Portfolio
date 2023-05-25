
#include "HashTable.h"

HashTable::HashTable() {
    capacity = 32;
    entries = new Entry*[capacity];
    occupied = 0;

    for(int i=0; i<capacity; i++) {
        entries[i] = nullptr;
    }
}

bool HashTable::insert(Song *song)
{
    reScale();

    int index = hash(song->getArtist());

    while (entries[index] && !entries[index]->isTomb)
        index = (index+1) % capacity;

    if(entries[index] != nullptr)
        delete entries[index];

    entries[index] = new Entry(song->getArtist(), song);

    occupied++;

    return true;
}

int HashTable::search(const string& key)
{
    int index = hash(key);

    while(entries[index])
    {
        if( entries[index]->key == key && !entries[index]->isTomb)
            return index;

        index = (index+1) % capacity;
    }

    return -1;
}
void HashTable::printSong(const string &key)
{
    int index = search(key);

    if(index == -1) {
        cout << "\nOOPS!! Song Not Found!.\n\n";
        return;
    }

    cout << '\n';
    while(entries[index])
    {
        if(!entries[index]->isTomb && entries[index]->key == key)
        {
            cout << *entries[index]->song;
            cout << '\n';
        }

        index = (index+1) % capacity;
    }
}

int HashTable::getOccupied() const
{
    return occupied;
}

bool HashTable::remove(const string& key)
{
    if(search(key) == -1)
        return false;

    int index = hash(key);
    int tempIndex = index;
    int count = 0;

    while(entries[index])
    {
        if(!entries[index]->isTomb && entries[index]->key == key)
            count++;

        index = (index+1) % capacity;
    }

    cout << "\nFound " << count << " Songs in the Library.\n";
    printSong(key);

    string title;
    if(count > 1)
    {
        cout << "\nEnter the Title of Song You wanted to Delete from above List: ";
        getline(cin, title);

        count = 0;
        while(entries[tempIndex]) {
            if (!entries[tempIndex]->isTomb && entries[tempIndex]->key == key && entries[tempIndex]->song->getTitle() == title) {
                count = 1;
                break;
            }

            tempIndex = (tempIndex + 1) % capacity;
        }

        if(count == 0)
        {
            cout << "\nOOPS!! Title Not Found.\n\n";
            return false;
        }
    } else {
        while(entries[tempIndex])
        {
            if(!entries[tempIndex]->isTomb && entries[tempIndex]->key == key)
                break;

            tempIndex = (tempIndex+1) % capacity;
        }
    }


    delete entries[tempIndex]->song;
    entries[tempIndex]->isTomb = true;
    occupied--;

    return true;
}

void HashTable::writeToFile(ostream& os)
{
    int i;

    for(i=0; i<capacity; i++)
        if(entries[i] && !entries[i]->isTomb)
            entries[i]->song->writeToFile(os);
}

HashTable::~HashTable() {
    int i;

    for(i=0; i<capacity; i++)
        if(entries[i]) {
            if(!entries[i]->isTomb)
                delete entries[i]->song;
            delete entries[i];
        }

    delete[] entries;
}
