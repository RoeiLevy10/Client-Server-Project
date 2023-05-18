#include "../include/KeyboardThread.h"

KeyboardThread::KeyboardThread(ConnectionHandler& ch) : ch(ch) {}

void KeyboardThread::run()
{
    while (!ch.ShouldTerminate()) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
		string line(buf);
        vector<string> ans;
        boost::split(ans, line, boost::is_any_of(" "));
        if(ans[0] == "summary")
        {
            ch.summaryCommand(line);
        }
        else
        {
            vector<string> backLine = ch.process(line);
            for(int i=0; (unsigned)i<backLine.size();i++)
            {
                cout<<"Client Send: \n" + backLine[i];
                if (!ch.sendFrameAscii(backLine[i],'\0')) { 
                    cout << "Disconnected. Exiting...\n" << endl;
                    break;
                }
            } 
        }                
    }
}