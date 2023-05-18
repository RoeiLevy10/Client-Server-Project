package bgu.spl.net.api;

import java.util.concurrent.ConcurrentHashMap;

public class ImpStompMessagingProtocol implements StompMessagingProtocol<String> {

    private ImpConnections connections = ImpConnections.getInstance();
    private int connection_Id;
    private boolean shouldTerminate = false;
    @Override
    public void start(int connectionId) {
        this.connection_Id = connectionId;
    }

    @Override
    public void process(String message) {
        Frame messageFrame = Frame.toFrame(message);
        switch(messageFrame.getTitle())
        {
            case "CONNECT":
                connenct(messageFrame);
                break;
            case "SEND":
                send(messageFrame);
                break;
            case "SUBSCRIBE":
                subscribe(messageFrame);
                break;
            case "UNSUBSCRIBE":
                unsubscribe(messageFrame);
                break;
            case "DISCONNECT":
                disconnect(messageFrame);
                break;
        }
    }

    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }

    private void connenct(Frame msg)
    {
        String userName = msg.getLogin();
        if(connections.getUserByUsername(userName) == null)
        {
            User us = new User(userName,msg.getPassword(),this.connection_Id);
            connections.getUsernamesToUsers().put(userName, us);
            if(connections.getConnIdToUser().get(connection_Id) != null)
            {
                Frame back = new Frame("ERROR", "", null, null, null, null, "client already logged in", msg, -1);
                connections.send(connection_Id, back.toString());
            }
            else
            {
               
                connections.getConnIdToUser().put(this.connection_Id, us);
                Frame back = new Frame("CONNECTED", "", null, null, null, null, null, null, null);
                connections.send(connection_Id, back.toString());
            }
        }
        else
        {
            User usExist = connections.getUserByUsername(userName);
            if(!usExist.password.equals(msg.getPassword()))
            {
                Frame back = new Frame("ERROR", "", null, null, null, null, "wrong password", msg, -1);
                connections.send(connection_Id, back.toString());
                connections.disconnect(connection_Id);
                this.shouldTerminate = true;
            }

            else if(usExist.active)
            {
                Frame back = new Frame("ERROR", "", null, null, null, null, "user already logged in", msg, -1);
                connections.send(connection_Id, back.toString()); 
                this.shouldTerminate = true;               
            }
            else
            {
                connections.getConnIdToUser().put(this.connection_Id, usExist);
                usExist.active = true;
                usExist.connectedId = this.connection_Id;
                Frame back = new Frame("CONNECTED", "", null, null, null, null, null, null, null);
                connections.send(connection_Id, back.toString());
            }
        }        
    }

    private void send (Frame msg)
    {
        ConcurrentHashMap<Integer, User> m1 = this.connections.getChannelsToUsers().get((msg.getDestination()));
        User us = this.connections.getUserByUsername(msg.getLogin());
        if(m1.get((Integer)(us.connectedId)) != null)
        {
            Frame messageToAll = new Frame("MESSAGE", msg.getBody(), msg.getLogin(), null, msg.getDestination(), msg.getSubscriptionId(), null, msg, null);
            this.connections.send(msg.getDestination(), messageToAll.toString());
        }
    }
    
    private void subscribe(Frame msg)
    {
        if(!this.connections.getChannelsToUsers().containsKey(msg.getDestination()))
        {
            ConcurrentHashMap<Integer,User> newList = new ConcurrentHashMap<>();
            this.connections.getChannelsToUsers().put(msg.getDestination(), newList);     
        }   
        User us = this.connections.getConnIdToUser().get(this.connection_Id);
        us.subToChannel.put(msg.getSubscriptionId(), msg.getDestination());
        ConcurrentHashMap<Integer,User> tmp =  this.connections.getChannelsToUsers().get(msg.getDestination());
        tmp.put(this.connection_Id, us);
        Frame receipt = new Frame("RECEIPT","", null, null, null, null, null, msg, msg.getReciepeId());
        this.connections.send(connection_Id, receipt.toString());
    }

    private void unsubscribe(Frame msg)
    {
        try
        {
            User us = this.connections.getConnIdToUser().get(this.connection_Id);
            if(us.subToChannel.containsKey(msg.getSubscriptionId()))
            {
                us.subToChannel.remove(msg.getSubscriptionId());
                ConcurrentHashMap<Integer,User> tmp =  this.connections.getChannelsToUsers().get(msg.getDestination());
                tmp.remove(this.connection_Id);
                Frame receipt = new Frame("RECEIPT","", null, null, null, null, null, msg, msg.getReciepeId());
                this.connections.send(connection_Id, receipt.toString());
            }
            else
            {
                Frame back = new Frame("ERROR", "", null, null, null, null, "user is not subscribe", msg, -1);
                connections.send(connection_Id, back.toString());  
                this.shouldTerminate = true;
            }
        }
        catch(NullPointerException e){}
    }

    private void disconnect(Frame msg)
    {
        this.connections.disconnect(connection_Id);
        this.shouldTerminate = true;
    }

    
}
