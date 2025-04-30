#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory> // for smart pointers
using namespace std;
// ========== Population Manager ==========
class PopulationManager {
private:
    int peasants;
    int nobles;
public:
    PopulationManager();
    void addPeasants(int n);
    void removePeasants(int n);
    void displayPopulation() const;
    int getPeasants() const;
    int getNobles() const;
    void save(ofstream& out) const;
    void load(ifstream& in);
};
// ========== Economy ==========
class Economy {
private:
    double gold;
public:
    Economy();
    double collectTax(int peasants, int nobles);
    void displayGold() const;
    double getGold() const;     
    void setGold(double value); 
    void applyInflation();
    void warImpactOnEconomy();
    void save(ofstream& out) const;
    void load(ifstream& in);
};
// ========== Social Class (Parent Class) ==========
class SocialClass {
protected:
    string name;
    int influence;

public:
    SocialClass(const string& name, int influence);
    virtual void displayStatus() const = 0; // Pure virtual
    virtual ~SocialClass() {}
};
class Peasant : public SocialClass {
public:
    Peasant();
    void displayStatus() const override;
};

class Noble : public SocialClass {
public:
    Noble();
    void displayStatus() const override;
};
class Merchant : public SocialClass {
public:
    Merchant();
    void displayStatus() const override;
};

// ========== Army ==========
class Army {
private:
    int totalSoldiers;
    double morale; // 0.0 to 1.0
    double salaryPerSoldier;

public:
    Army();
    void warImpactOnArmy();
    void recruitSoldiers(int number);
    void trainSoldiers();
    void paySoldiers(double& gold);
    void displayArmyStatus() const;
    int getTotalSoldiers() const;
    void save(ofstream& out) const;
    void load(ifstream& in);
   

};
// ========== Bank ==========
class Bank {
private:
    double treasury;
    double loanAmount;
    bool isCorrupt;

public:
    Bank();
    void requestLoan(double amount);
    void repayLoan(double amount);
    void performAudit();
    void displayBankStatus() const;
    void save(ofstream& out) const;
    void load(ifstream& in);
};
// ========== Leadership ==========
class Leadership {
private:
    string currentLeader;
    int leadershipStrength; // 0 (weak) to 100 (very strong)

public:
    Leadership();
    void holdElection(const string& newLeader);
    void attemptCoup();
    void displayLeaderStatus() const;
    void save(ofstream& out) const;
    void load(ifstream& in);
};
// ========== Resource Manager ==========
class ResourceManager {
private:
    int food;
    int wood;
    int stone;
    int iron;

public:
    ResourceManager();
    void collectResources(int foodAmount, int woodAmount, int stoneAmount, int ironAmount);
    void consumeResources(int foodAmount, int woodAmount, int stoneAmount, int ironAmount);
    void tradeResources(int foodTrade, int woodTrade, int stoneTrade, int ironTrade);
    void displayResources() const;
    int getFood() const;
    int getWood() const;
    int getStone() const;
    int getIron() const;
    void save(ofstream& out) const;
    void load(ifstream& in);
};
// ========== Event Manager ==========
class EventManager {
public:
    EventManager();
    void triggerRandomEvent(Army& army, Economy& economy, ResourceManager& resources, PopulationManager& population);

};

