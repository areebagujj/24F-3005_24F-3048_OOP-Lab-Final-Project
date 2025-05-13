#pragma warning(disable : 4996)
#ifndef ALLIANCE_H
#define ALLIANCE_H
#include <iostream>
#include <cstring>
using namespace std;
struct Alliance {
    char* kingdomA;
    char* kingdomB;
    Alliance(const char* k1, const char* k2) {
        kingdomA = new char[strlen(k1) + 1];
        kingdomB = new char[strlen(k2) + 1];
        strcpy(kingdomA, k1);
        strcpy(kingdomB, k2);
    }
    ~Alliance() {
        delete[] kingdomA;
        delete[] kingdomB;
    }
};
class AllianceSystem {
    Alliance** alliances;
    int count, capacity;
public:
    AllianceSystem(int cap = 20) {
        capacity = cap;
        count = 0;
        alliances = new Alliance * [capacity];
    }
    void formAlliance(const char* k1, const char* k2) {
        for (int i = 0; i < count; i++) {
            if ((strcmp(alliances[i]->kingdomA, k1) == 0 && strcmp(alliances[i]->kingdomB, k2) == 0) ||
                (strcmp(alliances[i]->kingdomA, k2) == 0 && strcmp(alliances[i]->kingdomB, k1) == 0)) {
                cout << "Alliance already exists.\n";
                return;
            }
        }
        if (count >= capacity) {
            cout << "Alliance limit reached.\n";
            return;
        }
        alliances[count++] = new Alliance(k1, k2);
        cout << "Alliance formed between " << k1 << " and " << k2 << ".\n";
    }
    bool areAllied(const char* k1, const char* k2) {
        for (int i = 0; i < count; i++) {
            if ((strcmp(alliances[i]->kingdomA, k1) == 0 && strcmp(alliances[i]->kingdomB, k2) == 0) ||
                (strcmp(alliances[i]->kingdomA, k2) == 0 && strcmp(alliances[i]->kingdomB, k1) == 0)) {
                return true;
            }
        }
        return false;
    }
    void viewAlliances(const char* kingdom) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (strcmp(alliances[i]->kingdomA, kingdom) == 0 || strcmp(alliances[i]->kingdomB, kingdom) == 0) {
                cout << "- " << alliances[i]->kingdomA << " & " << alliances[i]->kingdomB << endl;
                found = true;
            }
        }
        if (!found) cout << "No alliances found for " << kingdom << ".\n";
    }

    ~AllianceSystem() {
        for (int i = 0; i < count; i++) delete alliances[i];
        delete[] alliances;
    }
    void breakAlliance(const char* k1, const char* k2) {
        int allianceCount = 6;
        for (int i = 0; i < allianceCount; ++i) {
            if ((strcmp(alliances[i]->kingdomA, k1) == 0 && strcmp(alliances[i]->kingdomB, k2) == 0) ||
                (strcmp(alliances[i]->kingdomA, k2) == 0 && strcmp(alliances[i]->kingdomB, k1) == 0)) {

                cout << "Alliance between " << alliances[i]->kingdomA << " and " << alliances[i]->kingdomB << " has been broken.\n";

                delete alliances[i];

                // Shift remaining alliances
                for (int j = i; j < allianceCount - 1; ++j) {
                    alliances[j] = alliances[j + 1];
                }

                allianceCount--;
                return;  // ✅ Break after deleting one match
            }
        }
        cout << "No such alliance exists to break.\n";
    }

};
#endif

