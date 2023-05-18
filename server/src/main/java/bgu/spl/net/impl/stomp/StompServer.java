package bgu.spl.net.impl.stomp;

import java.util.function.Supplier;

import bgu.spl.net.api.ImpMessageEncoderDecoder;
import bgu.spl.net.api.ImpStompMessagingProtocol;
import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        Supplier<StompMessagingProtocol<String>> stm = () -> new ImpStompMessagingProtocol();
        Supplier<MessageEncoderDecoder<String>> med = () -> new ImpMessageEncoderDecoder();       
        if(args[1].equals("reactor"))
        {
            try (Server<String> server = Server.reactor(3,Integer.parseUnsignedInt(args[0]), stm, med)) {
                server.serve();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        else
        {
             try (Server<String> server = Server.threadPerClient(Integer.parseUnsignedInt(args[0]), stm, med)) {
                 server.serve();
             } catch (Exception e) {
                 e.printStackTrace();
             }
        }
    }
}
