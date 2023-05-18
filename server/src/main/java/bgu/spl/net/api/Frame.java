package bgu.spl.net.api;

import java.io.Serializable;

public class Frame implements Serializable {
    private String title;
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    private String body;
    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    private Integer reciepeId = 0; //RECIEPE + ALL FRAMES
    
    public Integer getReciepeId() {
        return reciepeId;
    }

    public void setReciepeId(Integer reciepeId) {
        this.reciepeId = reciepeId;
    }

    //CONNECT and CONNECTED FRAME
    private final double acceptVersion = 1.2;
    //CONNECT FRAME
    private final String host = "stomp.cs.bgu.ac.il";
    private String login;
    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    private String password;
    
    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    //MASSAGE and SEND and SUBSCRIBE FRAME
    private String destination;
    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    //MASSAGE and SUBSCRIBE and UNSUBSCRIBE FRAME
    private Integer subscriptionId;
    public Integer getSubscriptionId() {
        return subscriptionId;
    }

    public void setSubscriptionId(Integer subscriptionId) {
        this.subscriptionId = subscriptionId;
    }

    private static Integer messageId = 1;

    //ERROR
    private String errorMessage;//short description of the error
    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }

    private Frame theErrorMessage;

    public Frame getTheErrorMessage() {
        return theErrorMessage;
    }

    public void setTheErrorMessage(Frame theErrorMessage) {
        this.theErrorMessage = theErrorMessage;
    }

    public Frame (String title, String body, String login, String password, String destination, Integer subscriptionId, String message, Frame theMessage, Integer reciepeId)
    {
        this.title =title;
        if(title.equals("MESSAGE")) 
            messageId ++;
        this.body = body;
        this.login = login;
        this.password = password;
        this.destination = destination;
        this.subscriptionId = subscriptionId;
        this.errorMessage = message;
        this.theErrorMessage = theMessage;
        this.reciepeId = reciepeId;
    }

    public String toString()
    {
        String res= title;
        switch(res)
        {
            case "CONNECT":
                res += "\n" + "accept-version:" +  acceptVersion;
                res += "\n" + "host:" +  host;
                res += "\n" + "login:" +  login;
                res += "\n" + "passcode:" +  password;
                break;

            case "CONNECTED":
                res += "\n" + "version:" +  acceptVersion;
                break;

            case "MESSAGE":
                res += "\n" + "destination:" +  destination + "\n";
                res += "\n" + "user:" + login;
                res += "\n" + "message-id:" +  messageId;
                break;

            case "RECEIPT":
                res += "\n" + "receipt-id:" + reciepeId;
                break;

            case "SEND":
                res += "\n" + "destination:" +  destination + "\n";
                res += "\n" + "user:" + login;                
                break;

            case "SUBSCRIBE":
                res += "\n" + "destination:" +  destination;
                res += "\n" + "id:" +  subscriptionId;
                break;

            case "UNSUBSCRIBE":
                res += "\n" + "id:" +  subscriptionId;
                break;

            case "DISCONNECT":
                res += "\n" + "receipt:" +  reciepeId;
                break;
            
            default: //ERROR
                title = "ERROR";
                res = title;
                res += "\n" + "receipt-id:" +  reciepeId;
                res += "\n" + "message:" +  errorMessage;
                res += "\n" + "\nThe message:\n-----\n" +  theErrorMessage.toString()+"\n-----";
                break;
        }
        if(title.equals("ERROR"))
            res += "\n" + body;
        else res += "\n\n" + body;
        res += "\u0000";
        return res;
    }

    public static Frame toFrame(String theFrame)
    {
        String [] splitTheString = theFrame.split("\n");
        String res= splitTheString[0];
        switch(res)
        {
            case "CONNECT":
                return new Frame(res,"", splitTheString[3].split(":")[1], splitTheString[4].split(":")[1], null, null, null, null,null);

            case "CONNECTED":
                return new Frame(res,"", null, null, null, null, null, null,null);

            case "MESSAGE":
                String bodyStringMessage = "";
                for(int i = 4;i<splitTheString.length;i++)
                bodyStringMessage += splitTheString[i] + "\n";
                return new Frame(res,bodyStringMessage, splitTheString[3].split(":")[1], null, splitTheString[1].split(":")[1],null, null, null,null);

            case "RECEIPT":
                return new Frame(res,"", null, null, null, null, null, null,Integer.parseInt(splitTheString[1].split(":")[1]));

            case "ERROR":
                return new Frame(res,theFrame.split("-----")[2].substring(1), null, null, null, null, splitTheString[2].split(":")[1], toFrame(theFrame.split("-----")[1].substring(1)),Integer.parseInt(splitTheString[1].split(":")[1]));
                
            case "SEND":
                String bodyStringSend = "";
                for(int i = 4;i<splitTheString.length;i++)
                    bodyStringSend += splitTheString[i] + "\n";
                return new Frame(res,bodyStringSend, splitTheString[3].split(":")[1], null, splitTheString[1].split(":")[1], null, null, null,null);

            case "SUBSCRIBE":
                return new Frame(res,"", null, null, splitTheString[1].split(":")[1],Integer.parseInt(splitTheString[2].split(":")[1]), null, null,Integer.parseInt(splitTheString[3].split(":")[1]));

            case "UNSUBSCRIBE":
                return new Frame(res,"", null, null, null,Integer.parseInt(splitTheString[1].split(":")[1]), null, null,Integer.parseInt(splitTheString[2].split(":")[1]));

            case "DISCONNECT":
                return new Frame(res,"", null, null, null, null, null, null,Integer.parseInt(splitTheString[1].split(":")[1]));
        }
        return null;
    }
}
