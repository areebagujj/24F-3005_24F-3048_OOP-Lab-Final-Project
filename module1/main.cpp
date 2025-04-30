#include "Stronghold.h"
#include <fstream>
using namespace std;
void saveGame(PopulationManager& pop, Economy& eco, Army& army, Bank& bank, Leadership& leadership, ResourceManager& resources) {
    ofstream outFile("game_save.txt");
    if (!outFile) {
        cout << "Error opening file to save game.\n";
        return;
    }
    pop.save(outFile);
    eco.save(outFile);
    army.save(outFile);
    bank.save(outFile);
    leadership.save(outFile);
    resources.save(outFile);
    outFile.close();
    cout << " Game saved successfully!\n";
}
void loadGame(PopulationManager& pop, Economy& eco, Army& army, Bank& bank, Leadership& leadership, ResourceManager& resources) {
    ifstream inFile("game_save.txt");
    if (!inFile) {
        cout << "No saved game found.\n";
        return;
    }
    pop.load(inFile);
    eco.load(inFile);
    army.load(inFile);
    bank.load(inFile);
    leadership.load(inFile);
    resources.load(inFile);
    inFile.close();
    cout << "Game loaded successfully!\n";
}
void saveScore(PopulationManager& pop, Economy& eco, Army& army, Bank& bank, Leadership& leadership, ResourceManager& resources) {
    ofstream scoreFile("score.txt");
    if (!scoreFile) {
        cout << "Error opening file to save score.\n";
        return;
    }

    // Calculate a simple score based on values
    int totalPopulation = pop.getPeasants() + pop.getNobles();
    int totalArmy = army.getTotalSoldiers();
    double gold = eco.getGold();

    int totalResources = resources.getFood() + resources.getWood() + resources.getStone() + resources.getIron();

    int kingdomScore = (totalPopulation * 2) + (totalArmy * 3) + (gold / 10) + (totalResources / 5);

    // Save score
    scoreFile << "Kingdom Report\n";
    scoreFile << "---------------------------\n";
    scoreFile << "Total Population: " << totalPopulation << "\n";
    scoreFile << "Total Army Size: " << totalArmy << "\n";
    scoreFile << "Treasury Gold: " << gold << "\n";
    scoreFile << "Total Resources: " << totalResources << "\n";
    scoreFile << "---------------------------\n";
    scoreFile << "Total Kingdom Score: " << kingdomScore << "\n";

    scoreFile.close();
    cout << " Score saved successfully to 'score.txt'!\n";
}


int main() {
    PopulationManager population;
    Economy economy;
    Peasant peasant;
    Noble noble;
    Army army;
    Bank bank;
    Leadership leadership;
    ResourceManager resources;
    EventManager events;
    Merchant merchant;
    int choice;
    do {
        cout << "\n=== Stronghold Kingdom Management ===\n";
       cout << "2. Add Peasants\n";
       cout << "3. Remove Peasants\n";
       cout << "4. Collect Tax\n";
       cout << "5. Show Treasury\n";
       cout << "6. Show Social Classes\n";
       cout << "7. Recruit Soldiers\n";
       cout << "8. Train Army\n";
       cout << "9. Pay Soldiers\n";
       cout << "10. Show Army Status\n";
       cout << "11. Request Loan\n";
       cout << "12. Repay Loan\n";
       cout << "13. Perform Bank Audit\n";
       cout << "14. Show Bank Status\n";
       cout << "15. Hold Election\n";
       cout << "16. Attempt Coup\n";
       cout << "17. Show Leader Status\n";
       cout << "18. Collect Resources\n";
       cout << "19. Consume Resources\n";
       cout << "20. Show Resources\n";
       cout << "21. Trigger Random Event\n";
       cout << "22. Save Game\n";
       cout << "23. Load Game\n";
       cout << "24. Save Kingdom Score\n";
       cout << "25. Trade Resources\n";
       cout << "26. Apply Inflation\n";
       cout << "0. Exit\n";
       cout << "Enter your choice: ";
       cin >> choice;

        try {
            switch (choice) {
            case 1:
                population.displayPopulation();
                break;
            case 2: {
                int num;
                cout << "How many peasants to add? ";
                cin >> num;
                population.addPeasants(num);
                break;
            }
            case 3: {
                int num;
                cout << "How many peasants to remove? ";
                cin >> num;
                population.removePeasants(num);
                break;
            }
            case 4: {
                double collectedTax = economy.collectTax(population.getPeasants(), population.getNobles());
                cout << " Collected Tax: " << collectedTax << " gold!\n";
                break;
            }
            case 5:
                economy.displayGold();
                break;
            case 6:
                peasant.displayStatus();
                noble.displayStatus();
                merchant.displayStatus();
                break;
            case 7: {
                int num;
                cout << "How many soldiers to recruit? ";
                cin >> num;
                army.recruitSoldiers(num);
                break;
            }
            case 8:
                army.trainSoldiers();
                break;
            case 9: {
                double goldAvailable = economy.getGold();
                army.paySoldiers(goldAvailable);
                economy.setGold(goldAvailable); // Update economy after payment
                break;
            }

            case 10:
                army.displayArmyStatus();
                break;
            case 11: {
                double amount;
                cout << "Enter loan amount: ";
                cin >> amount;
                bank.requestLoan(amount);
                break;
            }
            case 12: {
                double amount;
                cout << "Enter repayment amount: ";
                cin >> amount;
                bank.repayLoan(amount);
                break;
            }
            case 13:
                bank.performAudit();
                break;
            case 14:
                bank.displayBankStatus();
                break;
            case 15: {
                string newLeader;
               cout << "Enter new leader name: ";
                cin.ignore(); // to clear the buffer
                getline(cin, newLeader);
                leadership.holdElection(newLeader);
                break;
            }
            case 16:
                leadership.attemptCoup();
                break;
            case 17:
                leadership.displayLeaderStatus();
                break;
            case 18: {
                int f, w, s, i;
                cout << "Enter amount of Food, Wood, Stone, Iron to collect: ";
                cin >> f >> w >> s >> i;
                resources.collectResources(f, w, s, i);
                break;
            }
            case 19: {
                int f, w, s, i;
                cout << "Enter amount of Food, Wood, Stone, Iron to consume: ";
                cin >> f >> w >> s >> i;
                resources.consumeResources(f, w, s, i);
                break;
            }
            case 20:
                resources.displayResources();
                break;
            case 21:
                events.triggerRandomEvent(army, economy, resources, population);
                break;

            case 22:
                saveGame(population, economy, army, bank, leadership, resources);
                break;
            case 23:
                loadGame(population, economy, army, bank, leadership, resources);
                break;
            case 24:
                saveScore(population, economy, army, bank, leadership, resources);
                break;
            case 25: {
                int f, w, s, i;
                cout << "Enter Food, Wood, Stone, Iron amounts to trade (positive to buy, negative to sell): ";
                cin >> f >> w >> s >> i;
                resources.tradeResources(f, w, s, i);
                break;
            }
            case 26:
                economy.applyInflation();
                break;

            case 0:
                cout << "Exiting game...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
        }
        catch (exception& e) {
            cout << "Error: " << e.what() <<endl;
        }

    } while (choice != 0);

    return 0;
}
