package bgu.spl.net.api.Messages.ClientMessages;

import bgu.spl.net.api.Messages.Message;
import bgu.spl.net.api.Messages.ServerMessages.ACK;
import bgu.spl.net.api.Messages.ServerMessages.Error;
import bgu.spl.net.api.Users.User;

public class COURSEREG extends Message {
    private int courseNum;

    public COURSEREG(int courseNum){
        super(Short.parseShort("5"));
        this.courseNum = courseNum;
    }

    @Override
    public Message process(User activeuser) {

        if(db.CourseRegister(activeuser,courseNum))
            return new ACK(Short.parseShort("5"));
        return new Error(Short.parseShort("5"));
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
