package bgu.spl.net.api;

import java.util.concurrent.ConcurrentHashMap;

public class User {
    
    public String userName;
    public ConcurrentHashMap<Integer,String> subToChannel;
    public String password;
    public boolean active = true;
    public int connectedId = -1;
    
    public User(String userName, String password,int connectedId)
    {
        this.userName = userName;
        this.subToChannel = new ConcurrentHashMap<>();
        this.password = password;
        this.connectedId = connectedId;
    }
}
