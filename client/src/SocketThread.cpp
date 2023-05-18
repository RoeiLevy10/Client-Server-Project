#include "../include/SocketThread.h"
#include "../include/Frame.h"
SocketThread::SocketThread(ConnectionHandler& ch) : ch(ch) {}

void SocketThread::run()
{
    vector<string> ans;
    while (!ch.ShouldTerminate()) {
        string str = "";
        if(ch.getLine(str))
        {           
            if(str!="")
            {   
                cout<<"Client recieved: \n" + str;
                boost::split(ans, str, boost::is_any_of("\n"));
                if(ans[0] == "ERROR")
                {
                    ch.setShouldTerminate(true);
                }
                if(ans[0] == "MESSAGE")
                {
                    ch.docodeMessage(str);
                }
            }
        }
    }
}