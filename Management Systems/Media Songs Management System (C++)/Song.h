#ifndef SONGS_SONG_H
#define SONGS_SONG_H

#include <iostream>
#include <cstring>

using namespace std;

class Song {
private:
    string title;
    string artist;
    int duration;

public:
    Song(const string title, const string artist, int duration);

    const string &getTitle() const;

    const string &getArtist() const;

    int getDuration() const;

    friend ostream &operator<<(ostream &os, const Song &song);

    ostream& writeToFile(ostream& os);
};

#endif //SONGS_SONG_H
