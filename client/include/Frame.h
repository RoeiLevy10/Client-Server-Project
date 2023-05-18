#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class Frame
{
private:
        string title;
        string body;
        const float acceptVersion = 1.2;
        const string host = "stomp.cs.bgu.ac.il";
        string login;
        string password;
        string destination;
        int subscriptionId;
        string errorMessage;
        string theErroredFrame;
        int receiptId;

public:
        string toString();
        string getTitle();
        string getBody();
        string getLogin();
        string getPassword();
        string getDestination();
        string getErrorMessage();
        string getHost();
        int getSubscriptionId();
        int getReceiptId();
        string getTheErroredFrame();
        float getAcceptVersion();

        virtual ~Frame();
        Frame(const Frame &other);
        Frame& operator=(const Frame &other);

        Frame (string title, string body, string login, string password, string destination, int subscriptionId, string errorMessage, string theErroredFrame, int reciepeId);
};