package bgu.spl.net.api.Messages.ServerMessages;

import bgu.spl.net.api.Messages.Message;
import bgu.spl.net.api.Users.User;

public class Error extends Message {
    private short MessageOp;

    public Error(short MessageOp) {
        super((short) 13);
        this.MessageOp = MessageOp;
    }

    @Override
    public Message process(User activeuser) {
        return null;
    }

    @Override
    public boolean isACK() {
        return false;
    }
}
