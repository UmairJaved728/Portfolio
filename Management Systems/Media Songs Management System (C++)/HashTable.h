#ifndef SONGS_HASHTABLE_H
#define SONGS_HASHTABLE_H

#include "Song.h"

class HashTable {
private:

    class Entry{
        public:
            string key;
            Song* song;
            bool isTomb;

            Entry(const string& key, Song* song)
            {
                this->key = key;
                this->song = song;
                this->isTomb = false;
            }
    };

    Entry **entries;
    int capacity;
    int occupied;

    void reScale()
    {
        double load = (double) occupied / (double) capacity;

        if(load <= 0.7)
            return;

        int oldCapacity = capacity;
        this->capacity = this->capacity * 2;
        auto **newEntries = new Entry *[this->capacity];

        for(int i=0; i<this->capacity; i++)
            newEntries[i] = nullptr;

        for(int i=0; i<oldCapacity; i++)
        {
            if( entries[i] && !entries[i]->isTomb )
            {
                int newIndex = hash(entries[i]->key);
                while (newEntries[newIndex])
                    newIndex = (newIndex + 1) % this->capacity;

                newEntries[newIndex] = entries[i];
            }
        }

        delete[] this->entries;
        this->entries = newEntries;
    }

    int hash(const string& key) const
    {
        int hashCode = 0, len = key.length();
        const int POWER_CONST = 31;

        for (int i = 0; i < len; i++)
            hashCode += key[i] * (POWER_CONST * i);

        return abs(hashCode) % capacity;
    }

public:
    HashTable();

    bool insert(Song *song);

    int search(const string& key);

    void printSong(const string& key);

    int getOccupied() const;

    bool remove(const string& key);;

    void writeToFile(ostream& os);

    virtual ~HashTable();
};


#endif //SONGS_HASHTABLE_H
