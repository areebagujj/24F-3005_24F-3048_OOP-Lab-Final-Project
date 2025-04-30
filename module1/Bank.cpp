#include "Stronghold.h"
#include <cstdlib> // For random corruption
using namespace std;
Bank::Bank() : treasury(10000.0), loanAmount(0.0), isCorrupt(false) {}

void Bank::requestLoan(double amount) {
    if (amount <= 0) {
        throw invalid_argument("Loan amount must be positive.");
    }
    treasury += amount;
    loanAmount += amount * 1.1; // 10% interest
   cout << "Loan granted. Remember to repay 110% of the amount!\n";

    // 20% chance corruption happens on loan
    if (rand() % 5 == 0) {
        isCorrupt = true;
        cout << "Warning: Corruption detected during loan processing!\n";
    }
}

void Bank::repayLoan(double amount) {
    if (amount <= 0) {
        throw invalid_argument("Repayment amount must be positive.");
    }
    if (amount > loanAmount) amount = loanAmount;
    loanAmount -= amount;
    treasury -= amount;
    cout << "Loan partially/fully repaid.\n";
}

void Bank::performAudit() {
    if (isCorrupt) {
       cout << "Audit failed! Bank is corrupt. Gold penalties applied.\n";
        treasury -= 500.0; // Penalty
        if (treasury < 0) treasury = 0;
    }
    else {
       cout << "Audit successful. No corruption found.\n";
    }
    isCorrupt = false; // Reset corruption
}

void Bank::displayBankStatus() const {
  cout << "Bank Treasury: " << treasury << "\n";
    cout << "Outstanding Loan: " << loanAmount << "\n";
    cout << "Corruption: " << (isCorrupt ? "Yes" : "No") << "\n";
}
void Bank::save(ofstream& out) const {
    out << treasury << " " << loanAmount << " " << isCorrupt << "\n";
}
void Bank::load(ifstream& in) {
    in >> treasury >> loanAmount >> isCorrupt;
}
