#include "../include/Frame.h"

using namespace std;

Frame::Frame (string title, string body, string login, string password, string destination, int subscriptionId, string errorMessage, string theErroredFrame, int receiptId) :
title(title), body(body), login(login), password(password), destination(destination), subscriptionId(subscriptionId), errorMessage(errorMessage), theErroredFrame(theErroredFrame), receiptId(receiptId)
{}

Frame::~Frame() {}

Frame::Frame(const Frame &other) : title(other.title), body(other.body), login(other.login), password(other.password), destination(other.destination), subscriptionId(other.subscriptionId), errorMessage(other.errorMessage), theErroredFrame(other.theErroredFrame), receiptId(other.receiptId) {}

Frame &Frame::operator=(const Frame &other)
{
    title = other.title;
    body = other.body;
    login = other.login;
    password = other.password;
    destination = other.destination;
    subscriptionId = other.subscriptionId;
    errorMessage = other.errorMessage;
    theErroredFrame = other.theErroredFrame;
    receiptId = other.receiptId;
    return *this;
}

string Frame ::getBody()
{
    return body;
}

string Frame :: toString()
{
    string res = title;
    if(res=="CONNECT")
    {
        res += "\naccept-version:" + to_string(acceptVersion);
        res += "\nhost:" +  host;
        res += "\nlogin:" +  login;
        res += "\npasscode:" +  password;
    }
    else if(res == "CONNECTED")
        res += "\nversion:" +  to_string(acceptVersion);            
    else if(res == "MESSAGE")
    {
        res += "\nsubscription:" + to_string(subscriptionId);
        res += "\ndestination:" +  destination;
    }
    else if(res == "RECEIPT")
        res += "\nreceipt-id:" + to_string(receiptId);
    else if(res == "ERROR")
    {
        res += "\nreceipt-id:" +  to_string(receiptId);
        res += "\nmessage:" +  errorMessage;
        res += "\n\nThe message:\n-----\n" +  theErroredFrame+"\n-----";
    }
    else if(res == "SEND")
    {
        res += "\ndestination:" +  destination;
        res += "\n\nuser:" + login; 
    }
    else if(res == "SUBSCRIBE")
    {
        res += "\ndestination:" +  destination;
        res += "\nid:" + to_string(subscriptionId);
        res += "\nreceipt:" + to_string(receiptId);
    }
    else if(res == "UNSUBSCRIBE")
    {
        res += "\nid:" + to_string(subscriptionId);
        res += "\nreceipt:" + to_string(receiptId);
    }
    else if(res == "DISCONNECT")
        res += "\nreceipt:" +  to_string(receiptId);
    
    if(body == "" ||title == "ERROR"||title == "SEND")
        res += "\n" + body;
    else res += "\n\n" + body;
        res += "\0";
    return res;
}
string Frame :: getTitle()
{
    return title;
}

string Frame :: getLogin()
{
    return login;
}
string Frame :: getPassword()
{
    return password;
}
string Frame :: getDestination()
{
    return destination;
}
string Frame :: getErrorMessage()
{
    return errorMessage;
}
string Frame :: getHost()
{
    return host;
}
int Frame :: getSubscriptionId()
{
    return subscriptionId;
}
int Frame :: getReceiptId()
{
    return receiptId;
}
string Frame :: getTheErroredFrame()
{
    return theErroredFrame;
}
float Frame :: getAcceptVersion()
{
    return acceptVersion;
}