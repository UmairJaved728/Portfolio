
#include "Song.h"

Song::Song(const string title, const string artist, int duration)
{
    this->title = title;
    this->artist = artist;
    this->duration = duration;
}

const string &Song::getTitle() const {
    return title;
}

const string &Song::getArtist() const {
    return artist;
}

int Song::getDuration() const {
    return duration;
}

ostream &operator<<(ostream &os, const Song &song) {
    os << "\tTitle: " << song.title << '\n' ;
    os << "\tArtist: " << song.artist << "\tDuration: " << song.duration << '\n';
    return os;
}

ostream& Song::writeToFile(ostream& os)
{
    os << title << '\t' << artist << '\t' << duration << '\n';
    return os;
}