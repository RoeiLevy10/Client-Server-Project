#include "../include/StompProtocol.h"

StompProtocol::StompProtocol() : valShouldTerminate(false), userName(), channelToSubId(),subId(1),receiptId(1),event(""),destToUserGame() {}

string StompProtocol::login(string &msg)
{
    vector<string> ans;
	boost::split(ans, msg, boost::is_any_of(" "));
	string ansToBack;
	if(ans[0] == "login")
	{
		Frame *back = new Frame("CONNECT","",ans[2],ans[3],"",0,"","",-1);
		ansToBack = back->toString();
        userName = ans[2];
		delete back;
        return ansToBack;
	}
    return NULL;
}

vector<string> StompProtocol::processCommand(string & msg)
{
	vector<string> ansToBack;
	vector<string> ans;
	boost::split(ans, msg, boost::is_any_of(" "));
	if(ans[0] == "join")
	{
		Frame *back = new Frame("SUBSCRIBE","","","",ans[1],getSubId(),"","",getReceiptId());		
		channelToSubId[ans[1]]=subId;
		subId++;
		receiptId++;
		vector<string> theGame;
		boost::split(theGame, ans[1], boost::is_any_of("_"));
		map<string,Game*> m1;
		m1[userName] = new Game(theGame[0],theGame[1]);
		destToUserGame[ans[1]] = m1;
		ansToBack.push_back(back->toString());
		delete back;
	}
	else if(ans[0] == "exit")
	{
		int subToBack = channelToSubId[ans[1]];
		Frame *back = new Frame("UNSUBSCRIBE","","","",ans[1],subToBack,"","",receiptId);
		receiptId++;
		channelToSubId.erase(ans[1]);
		ansToBack.push_back(back->toString());
		delete back;
	}
	else if(ans[0] == "logout")
	{
		Frame *back = new Frame("DISCONNECT","","","","",2,"","",receiptId);
		ansToBack.push_back(back->toString());
		delete back;
		channelToSubId.clear();
		valShouldTerminate = true;
	}
	else if(ans[0] == "report")
	{
		names_and_events res = parseEventsFile(ans[1]);
		int i =0;
		for(Event ev: res.events)
		{
			string body = "";
			body += "team a: " + ev.get_team_a_name() + "\n";
			body += "team b: " + ev.get_team_b_name() + "\n";
			body += "event name: " + ev.get_name() + "\n";
			body += "time: " + to_string(ev.get_time()) + "\n";
			body += "general game updates:\n" + mapToString(ev.get_game_updates());
			body += "team a updates:\n" + mapToString(ev.get_team_a_updates());
			body += "team b updates:\n" + mapToString(ev.get_team_b_updates());
			body += "description:\n" + ev.get_discription() + "\n";
			Frame *back = new Frame("SEND",body,userName,"", ev.get_team_a_name()+"_"+ ev.get_team_b_name(),2,"","",-1);
			ansToBack.push_back(back->toString());
			delete back;
			i++;
		}
	}	
	
	return ansToBack;
}

void StompProtocol::summaryCommand(string sumReqest)
{
	vector<string> ans;
	boost::split(ans, sumReqest, boost::is_any_of(" "));
	string dest = ans[1];
	string user = ans[2];
	string json_path = ans[3];
	map<string, Game*> mm = destToUserGame[dest];
	ofstream file(json_path);
	if(!file.is_open())
	{
		cout<<"unable to poen the file"<<endl;
	}
	else
	{
		file<<mm[user]->toString()<<endl;
		file.close();
		cout<<"succesfully written summary to file";
	}
}


void StompProtocol::docodeMessage(string message)
{
	//save in game class to specipic user
	vector<string> ans;
	boost::split(ans, message, boost::is_any_of("\n"));
	vector<string> theDest;
	boost::split(theDest, ans[1], boost::is_any_of(":"));
	vector<string> theUserName;
	boost::split(theUserName, ans[3], boost::is_any_of(":"));
	map<string, Game*> mm = destToUserGame[theDest[1]];
	if(destToUserGame[theDest[1]].count(theUserName[1]) == 1)
	{
		Game* g = mm[theUserName[1]];
		g -> updatesData(message);
	}
	else
	{
		vector<string> theTeams;
		boost::split(theTeams, theDest[1], boost::is_any_of("_"));
		Game* g = new Game(theTeams[0],theTeams[1]);
		g -> updatesData(message);
		mm[theUserName[1]] = g;
	}
}

void StompProtocol::setSouldTerminate(bool val)
{
	valShouldTerminate = val;
}

void StompProtocol::decodeError()
{
	valShouldTerminate = true;
}

string StompProtocol::getUserName()
{
	return userName;
}

void StompProtocol::setUserName(string user)
{
	userName = user;
}

bool StompProtocol::getShouldTerminate()
{
	return valShouldTerminate;
}

int StompProtocol::getSubId()
{
	return subId;
}

int StompProtocol::getReceiptId()
{
	return receiptId;
}

string StompProtocol::mapToString(const map<string, string> &event)
{
	string ret = "";
	for(const auto& i : event)
	{
		ret += "\t" + i.first + ": " + i.second + "\n";
	}
	return ret;
}