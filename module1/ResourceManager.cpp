#include "Stronghold.h"
using namespace std;
ResourceManager::ResourceManager() : food(500), wood(300), stone(200), iron(100) {}

void ResourceManager::collectResources(int foodAmount, int woodAmount, int stoneAmount, int ironAmount) {
    food += foodAmount;
    wood += woodAmount;
    stone += stoneAmount;
    iron += ironAmount;
    cout << "Resources collected successfully!\n";
}

void ResourceManager::consumeResources(int foodAmount, int woodAmount, int stoneAmount, int ironAmount) {
    if (foodAmount > food || woodAmount > wood || stoneAmount > stone || ironAmount > iron) {
        cout << "Not enough resources to consume!\n";
        return;
    }
    food -= foodAmount;
    wood -= woodAmount;
    stone -= stoneAmount;
    iron -= ironAmount;
    cout << "Resources consumed successfully!\n";
}

void ResourceManager::displayResources() const {
    cout << "Resources:\n";
    cout << "Food: " << food << "\n";
    cout << "Wood: " << wood << "\n";
    cout << "Stone: " << stone << "\n";
    cout << "Iron: " << iron << "\n";
}
int ResourceManager::getFood() const { return food; }
int ResourceManager::getWood() const { return wood; }
int ResourceManager::getStone() const { return stone; }
int ResourceManager::getIron() const { return iron; }


void ResourceManager::save(ofstream& out) const {
    out << food << " " << wood << " " << stone << " " << iron << "\n";
}

void ResourceManager::load(ifstream& in) {
    in >> food >> wood >> stone >> iron;
}
void ResourceManager::tradeResources(int foodTrade, int woodTrade, int stoneTrade, int ironTrade) {
    food += foodTrade;
    wood += woodTrade;
    stone += stoneTrade;
    iron += ironTrade;
    cout << "Trade successful! Resources updated.\n";
}

