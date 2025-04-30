#include "Stronghold.h"
#include <cstdlib>
#include <ctime>
using namespace std;
EventManager::EventManager() {
    srand(time(0));
}

void EventManager::triggerRandomEvent(Army& army, Economy& economy, ResourceManager& resources, PopulationManager& population) {
    int eventType = rand() % 5;

    switch (eventType) {
    case 0:
       cout << " Famine strikes the kingdom! Food supplies decrease.\n";
        resources.consumeResources(100, 0, 0, 0); 
        break;

    case 1:
        cout << " A deadly disease spreads! Population decreases.\n";
        population.removePeasants(15); 
        break;

    case 2:
        cout << " A surprise enemy attack occurs! Soldiers are injured.\n";
        army.warImpactOnArmy();            
        economy.warImpactOnEconomy();        
        break;

    case 3:
        cout << " Drought affects farms! Less food production.\n";
        resources.consumeResources(50, 0, 0, 0); 
        break;

    case 4:
        cout << " Betrayal! One noble switches sides.\n";
        population.removePeasants(5);                  
        economy.setGold(economy.getGold() - 200);        
        break;
    }
}
