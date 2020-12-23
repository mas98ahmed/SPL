package bgu.spl.net.api.Messages.ServerMessages;

import bgu.spl.net.api.Messages.Message;
import bgu.spl.net.api.Users.User;

import java.util.HashMap;

public class ACK extends Message {
    private short MessageOp;
    private String message;

    public ACK(short MessageOp){
        super((short) 12);
        this.MessageOp = MessageOp;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    @Override
    public Message process(User activeuser) {
        return null;
    }

    @Override
    public boolean isACK() {
        return true;
    }
}
