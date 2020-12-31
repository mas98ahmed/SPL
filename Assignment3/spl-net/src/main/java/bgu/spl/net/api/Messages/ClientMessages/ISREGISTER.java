package bgu.spl.net.api.Messages.ClientMessages;

import bgu.spl.net.api.Messages.Message;
import bgu.spl.net.api.Messages.ServerMessages.ACK;
import bgu.spl.net.api.Users.User;

public class ISREGISTER extends Message {
    private int courseNum;

    public ISREGISTER(int courseNum){
        super(Short.parseShort("9"));
        this.courseNum = courseNum;
    }

    @Override
    public Message process(User activeuser){
        ACK ack = new ACK(Short.parseShort("9"));
        ack.setMessage(activeuser.getCourses().contains(courseNum)? "REGISTERED" : "NOT REGISTERED");
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
