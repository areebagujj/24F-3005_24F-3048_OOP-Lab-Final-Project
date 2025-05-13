#pragma warning(disable : 4996)
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct Message {
    char* sender;
    char* receiver;
    char* content;
    Message(const char* s, const char* r, const char* c) {
        sender = new char[strlen(s) + 1];
        receiver = new char[strlen(r) + 1];
        content = new char[strlen(c) + 1];
        strcpy(sender, s);
        strcpy(receiver, r);
        strcpy(content, c);
    }
    ~Message() {
        delete[] sender;
        delete[] receiver;
        delete[] content;
    }
    void display() const {
        cout << "[" << sender << " to " << receiver << "]: " << content << endl;
    }
    void logToFile(ofstream& fout) const {
        fout << sender << "," << receiver << "," << content << endl;
    }
};
#endif

