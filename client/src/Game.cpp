#include "../include/Game.h"

Game::Game(string teamA, string teamB):team_a_update(),team_b_update(),general_game_update(),events(),teamA(teamA),teamB(teamB)
{
}

void Game:: updatesData(string msg)
{
    vector<string> ans;
    boost::split(ans, msg, boost::is_any_of("\n"));
    int j = 0;
    while(ans[j] != "general game updates:")
    {
        j++;
    }
    vector<string> findEventTime;
    boost::split(findEventTime, ans[j-1], boost::is_any_of(":"));
    events.push_back(findEventTime[1]);
    vector<string> findEventName;
    boost::split(findEventName, ans[j-2], boost::is_any_of(":"));
    events.push_back(findEventName[1]);
    j++;
    while(ans[j] != "team a updates:")
    {
        vector<string> insertTo;
        boost::split(insertTo, ans[j], boost::is_any_of(":"));
        general_game_update[insertTo[0]] = insertTo[1];
        j++;
    }
    j++;
    while(ans[j] != "team b updates:")
    {
        vector<string> insertTo;
        boost::split(insertTo, ans[j], boost::is_any_of(":"));
        team_a_update[insertTo[0]] = insertTo[1];
        j++;
    }
    j++;
    while(ans[j] != "description:")
    {
        vector<string> insertTo;
        boost::split(insertTo, ans[j], boost::is_any_of(":"));
        team_b_update[insertTo[0]] = insertTo[1];
        j++;
    }
    events.push_back(ans[j+1]);
}

string Game::toString()
{
    string res = "";
    res += teamA +" vs " +teamB +"\n";
    res +="Game stats:\n";
    res +="general stats:\n";
    res += mapToStirng(general_game_update);
    res += teamA +" stats:\n";
    res += mapToStirng(team_a_update);
    res += teamB +" stats:\n";
    res += mapToStirng(team_b_update);
    res += "Game event reports:\n";
    for(int i=0; (unsigned)i<events.size(); i+=3)
    {
        res += events[i] +" - " +events[i+1]+"\n\n"; 
        res += events[i+2]+"\n\n";
    }
    return res;
}

string Game::mapToStirng(const map<string, string> &event)
{
	string ret = "";
	for(const auto& i : event)
	{
		ret += i.first + ": " + i.second + "\n";
	}
	return ret;
}

Game::~Game() {}

Game::Game(const Game &other) : team_a_update(other.team_a_update) , team_b_update(other.team_b_update), general_game_update(other.general_game_update), events(other.events), teamA(other.teamA), teamB(other.teamB) {}

Game &Game::operator=(const Game &other)
{
    team_a_update = other.team_a_update;
    team_b_update = other.team_b_update;
    general_game_update = other.general_game_update;
    events = other.events;
    teamA = other.teamA;
    teamB = other.teamB;
    return *this;
}