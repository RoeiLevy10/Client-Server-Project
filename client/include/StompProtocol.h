#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../include/Frame.h"
#include "../include/event.h"
#include"../include/Game.h"
#include <fstream>
using namespace std;

class StompProtocol
{
private:
    bool valShouldTerminate;
    string userName ;
    map<string,int> channelToSubId;
    int subId;
	int receiptId;
    Event event;
    map<string,map<string,Game*>> destToUserGame;

public:
    StompProtocol();

    vector<string> processCommand(string &msg);

	void docodeMessage(string message);

	void decodeError();

	string getUserName();

    void setUserName(string user);

	void summaryCommand(string);

    bool getShouldTerminate();

    string login(string &msg);

    int getSubId();

    int getReceiptId();

    void setSouldTerminate(bool val);
    /*
    virtual ~StompProtocol();
    StompProtocol(const StompProtocol &other);
    StompProtocol& operator=(const StompProtocol &other);
    */

    string mapToString(const map<string, string> &event);
};
