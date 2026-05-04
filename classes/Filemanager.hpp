#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include "../data_structures/Linkedlist.hpp"
#include "Song.hpp"

using namespace std;

class FileManager {
public:
    static char detectDelimiter(const string& line);

    static bool parseSongLine(const string& line, char delimiter, Song& out);

    static bool loadSongs(const string& filePath, LinkedList<Song>& songs);

    static bool appendSong(const string& filePath, const Song& song, char delimiter);

    static bool saveSongs(const string& filePath, const LinkedList<Song>& songs, char delimiter);
};

#endif