package bgu.spl.net.api;

import java.io.IOException;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class ImpConnections implements Connections<String> {

    private ConcurrentHashMap<String,ConcurrentHashMap<Integer,User>> channelsToUsers = new ConcurrentHashMap<>();// channel to connection_id and User
    private ConcurrentHashMap<String,User> usernamesToUsers = new ConcurrentHashMap<>();// username to users
    private ConcurrentHashMap<Integer,User> connIdToUser = new ConcurrentHashMap<>();// connection_id to user
    private ConcurrentHashMap<Integer,ConnectionHandler> connIdToCh = new ConcurrentHashMap<>();// connection_id to connection_handler

    private static class SingletonHolder{
        private static ImpConnections instance = new ImpConnections();
    }
    public static ImpConnections getInstance(){
        return SingletonHolder.instance;
    }

    @Override
    public boolean send(int connectionId, String msg) {
        ConnectionHandler ch = connIdToCh.get(connectionId);
        if(ch != null) {
            ch.send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, String msg) {
        ConcurrentHashMap<Integer,User> tmpConnToUsers = this.channelsToUsers.get(channel);
        Set<Integer> allRegToChannel = tmpConnToUsers.keySet();
        for (Integer conn_id : allRegToChannel) {
            this.send(conn_id, msg);
        }
    }

    @Override
    public void disconnect(int connectionId) {
        try{ 
            if(connIdToUser.get(connectionId)!= null)
            {
                connIdToUser.get(connectionId).subToChannel.clear();    
                connIdToUser.get(connectionId).active = false;
                connIdToUser.get(connectionId).connectedId = -1; 
                connIdToUser.remove(connectionId);
            }   
            this.connIdToCh.get(connectionId).close();
            this.connIdToCh.remove(connectionId); 
        }
        catch(IOException e){}  
    }

    public ConcurrentHashMap<Integer,ConnectionHandler> getConnIdToCh()
    {
        return connIdToCh;
    }

    public User getUserByUsername(String username)
    {
        return usernamesToUsers.get(username);
    }

    public ConcurrentHashMap<String, User> getUsernamesToUsers() {
        return usernamesToUsers;
    }

    public void setUsernamesToUsers(ConcurrentHashMap<String, User> users) {
        this.usernamesToUsers = users;
    }

    public ConcurrentHashMap<Integer, User> getConnIdToUser() {
        return connIdToUser;
    }

    public void setConnIdToUser(ConcurrentHashMap<Integer, User> connToUser) {
        this.connIdToUser = connToUser;
    }

    public ConcurrentHashMap<String, ConcurrentHashMap<Integer, User>> getChannelsToUsers() {
        return channelsToUsers;
    }

    public void setChannelsToUsers(ConcurrentHashMap<String, ConcurrentHashMap<Integer, User>> channelsToUsers) {
        this.channelsToUsers = channelsToUsers;
    }

    public void addToconnIdToUser(int conId, User us)
    {
        this.connIdToUser.put(conId,us);
    }

}
