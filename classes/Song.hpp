#ifndef SONG_HPP
#define SONG_HPP

#include <string>

using namespace std;

class Song {
private:
    int id;
    string title;
    string artist;
    string album;
    int year;
    int durationSeconds;
    string filePath;

public:
    Song();

    Song(int id, string title, string artist, string album, int year, int durationSeconds, string filePath);

    int getId() const;
    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    int getYear() const;
    int getDurationSeconds() const;
    string getFilePath() const;

    void setId(int id);
    void setTitle(string title);
    void setArtist(string artist);
    void setAlbum(string album);
    void setYear(int year);
    void setDurationSeconds(int durationSeconds);
    void setFilePath(string filePath);

    string getFormattedDuration() const;

    string toFileString(char delimiter = ',') const;

    bool operator==(const Song& other) const;
    
};

#endif
