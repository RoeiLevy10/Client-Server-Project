#pragma once
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
class Game
{
private:
    map<string,string> team_a_update;
    map<string,string> team_b_update;
    map<string,string> general_game_update;
    vector<string> events;
    string teamA;
    string teamB;

public:
    string toString();
    void updatesData(string msg);
    Game(string teamA, string teamB);
    string mapToStirng(const map<string, string> &event);

    virtual ~Game();
    Game(const Game &other);
    Game& operator=(const Game &other);
};