#include "iostream"
#include "thread"
#include "boost/asio.hpp"
#include "../include/ConnectionHandler.h"
#include "../include/SocketThread.h"
#include "../include/KeyboardThread.h"
#include <vector>
#include "../include/Frame.h"
#include "../include/StompProtocol.h"
using namespace std;

int main (int argc, char *argv[]){
    const short bufsize = 1024;
    char buf[bufsize];
    cin.getline(buf, bufsize);
    string line(buf);
    vector<string> ans;
    boost::split(ans, line, boost::is_any_of(" "));
    vector<string>hostPort;
    boost::split(hostPort, ans[1], boost::is_any_of(":"));
    std::string host = hostPort[0];
    short port = stoi(hostPort[1]);
    //connect to server    
    ConnectionHandler con(host,port,StompProtocol ());
    if(!con.connect()){
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    con.logIn(line);
    KeyboardThread kb(con);
    SocketThread st(con);

    thread keyboard(&KeyboardThread::run, &kb);
    thread socket(&SocketThread::run, &st);
    
    socket.join();
    keyboard.join();
    con.close();
    return 0;


}