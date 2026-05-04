#include "Filemanager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

char FileManager::detectDelimiter(const string& line) {
    const string candidates = ",;:.-";

    char best = ',';
    int bestCount = 0;

    for (char delimiter : candidates) {
        int count = 0;
        for (char c : line) {
            if (c == delimiter) {
                count++;
            }
        }
        if (count == 6) return delimiter;

        if (count > bestCount) {
            bestCount = count;
            best = delimiter;
        }
    }

    return best;
}

bool FileManager::parseSongLine(const string& line, char delimiter, Song& out) {
    if (line.empty()) return false;

    stringstream ss(line);
    string fields[7];
    int count = 0;

    while (count < 7 && getline(ss, fields[count], delimiter)) {
        count++;
    }

    if (count != 7) return false;

    try {
        int id = stoi(fields[0]);
        string title = fields[1];
        string artist = fields[2];
        string album = fields[3];
        int year = stoi(fields[4]);
        int durationSeconds = stoi(fields[5]);
        string filePath = fields[6];

        out = Song(id, title, artist, album, year, durationSeconds, filePath);
        return true;
    } catch (const exception& e) {
        cerr << "Error parseando la linea: " << e.what() << endl;
        return false;
    }
}

bool FileManager::loadSongs(const string& filePath, LinkedList<Song>& songs) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filePath << endl;
        return false;
    }

    string line;
    char delimiter = ',';
    bool firstLine = true;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (!line.empty() && firstLine == '\r') {
            line.pop_back();
        }

        if (firstLine) {
            delimiter = detectDelimiter(line);
            firstLine = false;
        }

        Song song;
        if (parseSongLine(line, delimiter, song)) {
            songs.pushBack(song);
        } else {
            cout << "Error parseando la linea: " << line << endl;
        }
    }

    file.close();
    return !songs.isEmpty();
}

bool FileManager::saveSongs(const string& filePath, const LinkedList<Song>& songs, char delimiter) {
    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir: " << filePath << endl;
        return false;
    }

    auto* node = songs.getHead();
    while (node != nullptr) {
        file << node->data.toFileString(delimiter) << endl;
        node = node->next;
    }

    file.close();
    return true;
}

bool FileManager::appendSong(const string& filePath, const Song& song, char delimiter) {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir: " << filePath << endl;
        return false;
    }

    file << song.toFileString(delimiter) << endl;
    file.close();
    return true;
}