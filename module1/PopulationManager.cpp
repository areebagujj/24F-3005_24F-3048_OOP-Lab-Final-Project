#include "Stronghold.h"
using namespace std;
PopulationManager::PopulationManager() : peasants(100), nobles(10) {}
void PopulationManager::addPeasants(int n) {
    if (n < 0) throw invalid_argument("Cannot add negative peasants!");
    peasants += n;
}

void PopulationManager::removePeasants(int n) {
    if (n < 0) throw invalid_argument("Cannot remove negative peasants!");
    peasants =max(0, peasants - n);
}

void PopulationManager::displayPopulation() const {
    cout << "Peasants: " << peasants << ", Nobles: " << nobles << endl;
}
int PopulationManager::getPeasants() const {
    return peasants;
}

int PopulationManager::getNobles() const {
    return nobles;
}

void PopulationManager::save(ofstream& out) const {
    out << peasants << " " << nobles << "\n";
}

void PopulationManager::load(ifstream& in) {
    in >> peasants >> nobles;
}
