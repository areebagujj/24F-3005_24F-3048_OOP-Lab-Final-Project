#ifndef COMMUNICATION_SYSTEM_H
#define COMMUNICATION_SYSTEM_H

#include "Message.h"

class CommunicationSystem {
    Message** messages;
    int messageCount;
    int capacity;

public:
    CommunicationSystem(int cap = 100) {
        capacity = cap;
        messageCount = 0;
        messages = new Message * [capacity];
    }

    ~CommunicationSystem() {
        for (int i = 0; i < messageCount; ++i)
            delete messages[i];
        delete[] messages;
    }

    void sendMessage(const char* sender, const char* receiver, const char* content) {
        if (messageCount >= capacity) {
            cout << "Message limit reached.\n";
            return;
        }
        messages[messageCount] = new Message(sender, receiver, content);
        ofstream fout("chat_log.txt", ios::app);
        if (fout.is_open()) {
            messages[messageCount]->logToFile(fout);
            fout.close();
        }
        messageCount++;
    }

    void viewMessages(const char* kingdomName) const {
        cout << "\nMessages involving " << kingdomName << ":\n";
        for (int i = 0; i < messageCount; ++i) {
            if (strcmp(messages[i]->sender, kingdomName) == 0 || strcmp(messages[i]->receiver, kingdomName) == 0) {
                messages[i]->display();
            }
        }
    }
};

#endif

