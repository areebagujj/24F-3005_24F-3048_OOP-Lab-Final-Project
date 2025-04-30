#include "Stronghold.h"
#include <cstdlib> // For random coup chance
using namespace std;
Leadership::Leadership() : currentLeader("King Arthur"), leadershipStrength(70) {}

void Leadership::attemptCoup() {
    int chance = rand() % 100;
    if (chance > leadershipStrength) {
        cout << "Coup successful! The leader has been overthrown!\n";
        currentLeader = "No Leader";
        leadershipStrength = 0;
    }
    else {
       cout << "Coup failed! The leader remains in power.\n";
        leadershipStrength -= 10;
        if (leadershipStrength < 0) leadershipStrength = 0;
    }
}

void Leadership::displayLeaderStatus() const {
   cout << "Current Leader: " << currentLeader << "\n";
  cout << "Leadership Strength: " << leadershipStrength << "%\n";
}

void Leadership::save(ofstream& out) const {
    out << currentLeader << " " << leadershipStrength << "\n";
}

void Leadership::load(ifstream& in) {
    in >> currentLeader >> leadershipStrength;
}
void Leadership::holdElection(const string& newLeader) {
    currentLeader = newLeader;
    leadershipStrength = rand() % 51 + 50; // Random strength between 50-100
    cout << "New leader elected: " << currentLeader << "\n";
   cout << "Leadership Strength: " << leadershipStrength << "%\n";

    // Special behavior for some leaders
    if (currentLeader == "King Arthur") {
        cout << "King Arthur inspires the people. Economy and army morale boosted!\n";
    }
    else if (currentLeader == "King Richard") {
        cout << "King Richard focuses on military expansion. Army training improved!\n";
    }
}
