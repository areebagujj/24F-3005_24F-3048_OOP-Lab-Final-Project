#ifndef WAR_SYSTEM_H
#define WAR_SYSTEM_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct WarEvent {
    char* attacker;
    char* defender;
    bool wasBetrayal;
    WarEvent(const char* a, const char* d, bool betrayal) {
        attacker = new char[strlen(a) + 1];
        defender = new char[strlen(d) + 1];
        strcpy(attacker, a);
        strcpy(defender, d);
        wasBetrayal = betrayal;
    }
    ~WarEvent() {
        delete[] attacker;
        delete[] defender;
    }
    void display() const {
        if (wasBetrayal)
            cout << attacker << " has betrayed " << defender << " and declared war!\n";
        else
            cout << attacker << " has declared war on " << defender << ".\n";
    }

    void logToFile(ofstream& fout) const {
        fout << attacker << "," << defender << "," << (wasBetrayal ? "Betrayal" : "War") << endl;
    }
};
class WarSystem {
    WarEvent** events;
    int count;
    int capacity;
public:
    WarSystem(int cap = 100) {
        capacity = cap;
        count = 0;
        events = new WarEvent * [capacity];
    }
    ~WarSystem() {
        for (int i = 0; i < count; ++i)
            delete events[i];
        delete[] events;
    }
    void declareWar(const char* attacker, const char* defender, bool isBetrayal) {
        if (count >= capacity) {
            cout << "War log full.\n";
            return;
        }
        events[count] = new WarEvent(attacker, defender, isBetrayal);
        events[count]->display();

        ofstream fout("war_log.txt", ios::app);
        if (fout.is_open()) {
            events[count]->logToFile(fout);
            fout.close();
        }

        count++;
    }

    void viewAllWars() const {
        cout << "\n=== WAR EVENTS ===\n";
        for (int i = 0; i < count; ++i)
            events[i]->display();
    }
};

#endif

