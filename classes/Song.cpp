#include "Song.hpp"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Song::Song()
    : id(0), title(""), artist(""), album(""), year(0), durationSeconds(0), filePath("") {}

Song::Song(int id, string title, string artist, string album, int year, int durationSeconds, string filePath)
    : id(id), title(title), artist(artist), album(album), year(year), durationSeconds(durationSeconds), filePath(filePath) {}

int Song::getId() const {
    return id;
}

string Song::getTitle() const {
    return title;
}

string Song::getArtist() const {
    return artist;
}

string Song::getAlbum() const {
    return album;
}

int Song::getYear() const {
    return year;
}

int Song::getDurationSeconds() const {
    return durationSeconds;
}

string Song::getFilePath() const {
    return filePath;
}

void Song::setId(int id) {
    this->id = id;
}

void Song::setTitle(string title) {
    this->title = title;
}

void Song::setArtist(string artist) {
    this->artist = artist;
}

void Song::setAlbum(string album) {
    this->album = album;
}

void Song::setYear(int year) {
    this->year = year;
}

void Song::setDurationSeconds(int durationSeconds) {
    this->durationSeconds = durationSeconds;
}

void Song::setFilePath(string filePath) {
    this->filePath = filePath;
}

string Song::getFormattedDuration() const {
    int minutes = durationSeconds / 60;
    int seconds = durationSeconds % 60;

    stringstream ss;
    ss << minutes << ":" << setw(2) << setfill('0') << seconds;
    return ss.str();
}

string Song::toFileString(char delimiter) const {
    stringstream ss;
    ss << id << delimiter
       << title << delimiter
       << artist << delimiter
       << album << delimiter
       << year << delimiter
       << durationSeconds << delimiter
       << filePath;
    return ss.str();
}

bool Song::operator==(const Song& other) const {
    return id == other.id;
}