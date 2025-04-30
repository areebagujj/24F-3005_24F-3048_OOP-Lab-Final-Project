#include "Stronghold.h"
using namespace std;
SocialClass::SocialClass(const string& n, int inf) : name(n), influence(inf) {}
Peasant::Peasant() : SocialClass("Peasant", 1) {}

void Peasant::displayStatus() const {
   cout << "Class: " << name << ", Influence: " << influence << endl;
}

Noble::Noble() : SocialClass("Noble", 10) {}

void Noble::displayStatus() const {
    cout << "Class: " << name << ", Influence: " << influence << endl;
}
Merchant::Merchant() : SocialClass("Merchant", 5) {}

void Merchant::displayStatus() const {
    cout << "Class: " << name << ", Influence: " << influence << endl;
}
