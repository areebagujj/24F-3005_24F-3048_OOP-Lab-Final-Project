#ifndef MAP_SYSTEM_H
#define MAP_SYSTEM_H
#include <iostream>
#include <iomanip>
using namespace std;
const int MAP_ROWS = 20;
const int MAP_COLS = 40;
const int NAME_LENGTH = 10;
class MapSystem {
    char grid[MAP_ROWS][MAP_COLS][NAME_LENGTH];
public:
    MapSystem() {
        for (int i = 0; i < MAP_ROWS; ++i)
            for (int j = 0; j < MAP_COLS; ++j)
                setEmpty(grid[i][j]);
    }
    void setEmpty(char cell[]) {
        cell[0] = '.';
        cell[1] = '\0';
    }
    void copyName(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0' && i < NAME_LENGTH - 1) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    bool isEqual(const char* a, const char* b) {
        int i = 0;
        while (a[i] != '\0' && b[i] != '\0') {
            if (a[i] != b[i]) return false;
            i++;
        }
        return a[i] == '\0' && b[i] == '\0';
    }
    void placeKingdom(const char* name, int row, int col) {
        if (row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLS) {
            copyName(grid[row][col], name);
        }
        else {
            cout << "Invalid coordinates!\n";
        }
    }
    void moveKingdom(const char* name, int newRow, int newCol) {
        bool found = false;

        for (int i = 0; i < MAP_ROWS; ++i) {
            for (int j = 0; j < MAP_COLS; ++j) {
                if (isEqual(grid[i][j], name)) {
                    setEmpty(grid[i][j]);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found) {
            placeKingdom(name, newRow, newCol);
        }
        else {
            cout << "Kingdom not found on the map.\n";
        }
    }
    void displayMap() {
        cout << "\n=== KINGDOM MAP ===\n\n";
        for (int i = 0; i < MAP_ROWS; ++i) {
            for (int j = 0; j < MAP_COLS; ++j) {
                cout << setw(4) << grid[i][j];
            }
            cout << endl;
        }
        cout << "\nLegend: '.' = Empty | Kingdom names show position\n\n";
    }
};
#endif

