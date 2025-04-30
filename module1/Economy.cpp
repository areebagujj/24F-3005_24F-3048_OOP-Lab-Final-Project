#include "Stronghold.h"
using namespace std;
Economy::Economy() : gold(5000.0) {}
double Economy::collectTax(int peasants, int nobles) {
    double tax = peasants * 2 + nobles * 10;
    gold += tax;
    return tax;
}
void Economy::displayGold() const {
   cout << "Gold in Treasury: " << gold << endl;
  

}
double Economy::getGold() const {
    return gold;
};

void Economy::setGold(double value) {
    gold = value;
};

void Economy::save(ofstream& out) const {
    out << gold << "\n";
}

void Economy::load(ifstream& in) {
    in >> gold;
}
void Economy::applyInflation() {
    gold *= 0.98; // decrease value slightly to simulate inflation
    cout << "Inflation applied: Treasury devalued slightly.\n";
}
void Economy::warImpactOnEconomy() {
    gold -= 300; // 300 gold spent in war
    if (gold < 0) gold = 0;
    cout << " War Expense: 300 gold spent from treasury!\n";
}

