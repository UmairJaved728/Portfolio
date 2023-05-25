#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Song.h"
#include "HashTable.h"
#include <sstream>

TEST_CASE("Song class tests") {
    const string title = "Hey Jude";
    const string artist = "The Beatles";
    const int duration = 7 * 60 + 11;
    Song song(title, artist, duration);

    SECTION("Test getTitle method") {
        REQUIRE(song.getTitle() == title);
    }

    SECTION("Test getArtist method") {
        REQUIRE(song.getArtist() == artist);
    }

    SECTION("Test getDuration method") {
        REQUIRE(song.getDuration() == duration);
    }

    SECTION("Test output stream operator") {
        stringstream ss;
        ss << song;
        string output = ss.str();
        REQUIRE(output.find(title) != string::npos);
        REQUIRE(output.find(artist) != string::npos);
        REQUIRE(output.find(to_string(duration)) != string::npos);
    }

    SECTION("Test writeToFile method") {
        stringstream ss;
        song.writeToFile(ss);
        string output = ss.str();
        REQUIRE(output.find(title) != string::npos);
        REQUIRE(output.find(artist) != string::npos);
        REQUIRE(output.find(to_string(duration)) != string::npos);
    }
}
TEST_CASE("Song Class") {

    SECTION("Song Constructor") {
        Song song("title", "artist", 120);
        REQUIRE(song.getTitle() == "title");
        REQUIRE(song.getArtist() == "artist");
        REQUIRE(song.getDuration() == 120);
    }

    SECTION("Song Output Operator") {
        Song song("title", "artist", 120);
        std::stringstream stream;
        stream << song;
        std::string expectedOutput = "\tTitle: title\n\tArtist: artist\tDuration: 120\n";
        REQUIRE(stream.str() == expectedOutput);
    }

    SECTION("Song Write to File") {
        Song song("title", "artist", 120);
        std::stringstream stream;
        song.writeToFile(stream);
        std::string expectedOutput = "title\tartist\t120\n";
        REQUIRE(stream.str() == expectedOutput);
    }
}

TEST_CASE("HashTable Class") {

    SECTION("HashTable Insert and Search") {
        HashTable table;
        Song song1("song1", "artist1", 120);
        Song song2("song2", "artist2", 180);

        table.insert(&song1);
        table.insert(&song2);

        REQUIRE(table.getOccupied() == 2);

        int index1 = table.search("artist1");
        int index2 = table.search("artist2");

        REQUIRE(index1 != -1);
        REQUIRE(index2 != -1);
    }

    SECTION("HashTable Remove") {
        HashTable table;
        Song song1("song1", "artist1", 120);
        Song song2("song2", "artist2", 180);

        table.insert(&song1);
        table.insert(&song2);

        REQUIRE(table.getOccupied() == 2);

        REQUIRE(table.remove("artist1") == true);
        REQUIRE(table.getOccupied() == 1);

        REQUIRE(table.search("artist1") == -1);
    }

    SECTION("HashTable Write to File") {
        HashTable table;
        Song song1("song1", "artist1", 120);
        Song song2("song2", "artist2", 180);
        Song song3("song3", "artist3", 240);

        table.insert(&song1);
        table.insert(&song2);
        table.insert(&song3);

        std::stringstream stream;
        table.writeToFile(stream);
        std::string expectedOutput = "song3\tartist3\t240\nsong2\tartist2\t180\nsong1\tartist1\t120\n";
        REQUIRE(stream.str() == expectedOutput);
    }
}