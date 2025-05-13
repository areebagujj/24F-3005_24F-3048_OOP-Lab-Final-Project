#include "Stronghold.h"
#include "CommunicationSystem.h"
#include "Alliance.h"
#include "WarSystem.h"
#include "MapSystem.h"
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

    double kingdomScore = (totalPopulation * 2) + (totalArmy * 3) + (gold / 10) + (totalResources / 5);

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
void messagesys()
{
        CommunicationSystem comms;
        const int MAX = 100;
        char sender[MAX], receiver[MAX], content[MAX];
        int choice;

        do {
            cout << "\n--- Messaging System ---\n";
            cout << "1. Send Message\n";
            cout << "2. View Messages\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(); // Ignore newline

            if (choice == 1) {
                cout << "Enter Sender Kingdom: ";
                cin.getline(sender, MAX);
                cout << "Enter Receiver Kingdom: ";
                cin.getline(receiver, MAX);
                cout << "Enter Message Content: ";
                cin.getline(content, MAX);
                comms.sendMessage(sender, receiver, content);
                cout << "Message sent!\n";
            }
            else if (choice == 2) {
                cout << "Enter Kingdom Name to View Messages: ";
                cin.getline(sender, MAX); // reuse sender as input
                comms.viewMessages(sender);
            }
            else if (choice != 3) {
                cout << "Invalid choice.\n";
            }

        } while (choice != 3);

        cout << "Goodbye!\n";
        return;

}
void alliancesys()
{
        AllianceSystem alliances;
        CommunicationSystem comms;

        char k1[100], k2[100];
        int choice;

        while (true) {
            cout << "\n--- MENU ---\n";
            cout << "1. Form Alliance\n";
            cout << "2. Check Alliance\n";
            cout << "3. View Alliances of a Kingdom\n";
            cout << "4. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "Enter Kingdom A: ";
                cin.getline(k1, 100);
                cout << "Enter Kingdom B: ";
                cin.getline(k2, 100);
                alliances.formAlliance(k1, k2);

            }
            else if (choice == 2) {
                cout << "Enter Kingdom A: ";
                cin.getline(k1, 100);
                cout << "Enter Kingdom B: ";
                cin.getline(k2, 100);
                if (alliances.areAllied(k1, k2))
                    cout << "They are allied.\n";
                else
                    cout << "No alliance found.\n";

            }
            else if (choice == 3) {
                cout << "Enter Kingdom Name: ";
                cin.getline(k1, 100);
                alliances.viewAlliances(k1);

            }
            else if (choice == 4) {
                cout << "Exiting...\n";
                return;

            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        return ;
}
void warsys(int choice)
{
        AllianceSystem allianceSystem;
        WarSystem warSystem;
        char attacker[100], defender[100];
            if (choice == 1) {
                cout << "Enter attacker kingdom: ";
                cin.getline(attacker, 100);
                cout << "Enter defender kingdom: ";
                cin.getline(defender, 100);

                bool betrayal = allianceSystem.areAllied(attacker, defender);
                if (betrayal)
                    cout << "[!] Betrayal detected. This was an alliance before.\n";

                warSystem.declareWar(attacker, defender, betrayal);

                if (betrayal)
                    allianceSystem.breakAlliance(attacker, defender);
            }
            else if (choice == 4) {
                warSystem.viewAllWars();
            }
            else if (choice == 0) {
                cout << "Exiting...\n";
                return;
            }
            else {
                cout << "Invalid choice.\n";
            }
        return;
}
void mapsys()
{
        MapSystem map;
        char kname[NAME_LENGTH];
        int row, col;
        cout << "Enter kingdom name: ";
        cin >> kname;
        cout << "Enter coordinates (row col): ";
        cin >> row >> col;
        map.placeKingdom(kname, row, col);
        map.displayMap();
        // Move kingdom
        cout << "Move " << kname << " to new position:\n";
        cout << "Enter new coordinates (row col): ";
        cin >> row >> col;
        map.moveKingdom(kname, row, col);
        map.displayMap();
        return;
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
    int ch;
    do
    {
    cout << "Select the mode you want to go to: \n1. Single own kingdom management.\n 2. Multi interactions with other kingdoms\n";
    cin >> ch;
    if (ch == 1)
    {
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
            cout << "27. Enter multiplayer\n";
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
                cout << "Error: " << e.what() << endl;
            }

        } while (choice != 0);

    }
    else if (ch == 2)
    {
        int p;
        do
        {
        cout << "choose the function u want : \n1. Communication with other kingdom\n2. Alliance system\n3. Declare War\n4. View kingdoms map\n0. exit\nChoice: ";
        cin >> p;
        switch (p) 
        {

        case 1:
            messagesys();
            break;
        case 2:
            alliancesys();
        case 3:
            cout << "\n1. Declare War\n2. View War Log\n0. Exit\nChoice: ";
            cin >> choice;
            warsys(choice);
            if (choice == 1)
            {
                resources.consumeResources(100, 100, 100, 100);
                army.decreaseMorale();
            }
        case 4:
            mapsys();
        }   

        } while (p != 0);
    }

    } while (ch != 0);
    cout << "THANKYOU FOR PLAYING STRONGHOLD\n";
    return 0;
}
