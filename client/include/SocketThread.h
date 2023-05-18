#pragma once
#include "../include/ConnectionHandler.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
using namespace std;

class SocketThread
{
    private:
        ConnectionHandler& ch;
    public:
        SocketThread(ConnectionHandler& ch);
        void run();
};