#include "Stronghold.h"
using namespace std;
Army::Army() : totalSoldiers(50), morale(0.7), salaryPerSoldier(10.0) {}
void Army::recruitSoldiers(int number) {
    if (number < 0) throw invalid_argument("Cannot recruit negative soldiers!");
    totalSoldiers += number;
    morale -= 0.05; // new recruits lower morale slightly
    if (morale < 0.0) morale = 0.0;
}
void Army::trainSoldiers() {
    morale += 0.1;
    if (morale > 1.0) morale = 1.0;
    cout << "Training complete. Morale increased!\n";
}
void Army::decreaseMorale()
{
    morale -= 10;
}
void Army::paySoldiers(double& gold) {
    double totalPay = totalSoldiers * salaryPerSoldier;
    if (gold >= totalPay) {
        gold -= totalPay;
       cout << "Soldiers paid successfully.\n";
        morale += 0.05;
    }
    else {
       cout << "Not enough gold to pay soldiers! Morale drops!\n";
        morale -= 0.1;
    }

    if (morale > 1.0) morale = 1.0;
    if (morale < 0.0) morale = 0.0;
}

void Army::displayArmyStatus() const {
    cout << "Total Soldiers: " << totalSoldiers << "\n";
 cout << "Army Morale: " << morale * 100 << "%\n";
}
int Army::getTotalSoldiers() const {
    return totalSoldiers;
}

void Army::save(ofstream& out) const {
    out << totalSoldiers << " " << morale << "\n";
}

void Army::load(ifstream& in) {
    in >> totalSoldiers >> morale;
}
void Army::warImpactOnArmy() {
    if (totalSoldiers > 10) {
        totalSoldiers -= 10; // 10 soldiers die
    }
    else {
        totalSoldiers = 0;
    }
    morale -= 0.2; // morale drops
    if (morale < 0.0) morale = 0.0;

    cout << " War Impact: 10 soldiers lost, morale decreased!\n";
}



