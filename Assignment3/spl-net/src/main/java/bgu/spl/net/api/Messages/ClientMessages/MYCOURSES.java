package bgu.spl.net.api.Messages.ClientMessages;

import bgu.spl.net.api.Messages.Message;
import bgu.spl.net.api.Messages.ServerMessages.ACK;
import bgu.spl.net.api.Users.User;

public class MYCOURSES extends Message {
    public MYCOURSES() {
        super(Short.parseShort("11"));
    }

    @Override
    public Message process(User activeuser) {
        ACK ack = new ACK(Short.parseShort("11"));
        ack.setMessage(activeuser.getCourses().toString());
        return ack;
    }

    @Override
    public boolean isACK() {
        return false;
    }

    @Override
    public byte[] encode() {
        return null;
    }
}
