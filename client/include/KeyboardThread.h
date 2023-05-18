#pragma once
#include "../include/ConnectionHandler.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
using namespace std;

class KeyboardThread
{
    private:
        ConnectionHandler& ch;

    public:
        KeyboardThread(ConnectionHandler& ch);
        void run();
};