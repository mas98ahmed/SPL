package bgu.spl.net.api;

import bgu.spl.net.api.Messages.ClientMessages.*;
import bgu.spl.net.api.Messages.Message;

import java.nio.charset.StandardCharsets;
import java.util.*;

public class MessageEncoderDecoderImpl implements MessageEncoderDecoder<Message> {
    private short Opcode = 0;
    private List<Byte> bytes = new LinkedList<>();
    private int zeroByteNum = 0;

    @Override
    public Message decodeNextByte(byte nextByte) {
        if (Opcode == 0) {
            bytes.add(nextByte);
        }
        if (bytes.size() >= 2) {
            byte[] op = new byte[2];
            op[0] = bytes.get(0);
            op[1] = bytes.get(1);
            Opcode = bytesToShort(op);
            if (Opcode == 1 || Opcode == 2 || Opcode == 3) {
                bytes.add(nextByte);
                if(nextByte == 0){
                    zeroByteNum++;
                }
                if(zeroByteNum == 2){
                    String username = DecodeIntoString(bytes.subList(2, bytes.indexOf(0)));
                    String password = DecodeIntoString(bytes.subList(bytes.indexOf(0) + 1, bytes.size() - 1));
                    if (Opcode == 1) {
                        return new ADMINREG(username, password);
                    }
                    if (Opcode == 2) {
                        return new STUDENTREG(username, password);
                    }
                    if (Opcode == 3) {
                        return new LOGIN(username, password);
                    }
                    bytes.clear();
                    zeroByteNum = 0;
                    Opcode = 0;
                }
            }
            if (Opcode == 4 || Opcode == 11) {
                if (Opcode == 4) {
                    Opcode = 0;
                    bytes.clear();
                    return new LOGOUT();
                } else {
                    Opcode = 0;
                    bytes.clear();
                    return new MYCOURSES();
                }
            }
            if (Opcode == 5 || Opcode == 6 || Opcode == 7 || Opcode == 9 || Opcode == 10) {
                bytes.add(nextByte);
                if(nextByte == 0){
                    zeroByteNum++;
                }
                byte[] courseNum = new byte[2];
                courseNum[0] = bytes.get(2);
                courseNum[1] = bytes.get(3);
                short course = bytesToShort(courseNum);
                if (Opcode == 5) {
                    return new COURSEREG(course);
                }
                if (Opcode == 6) {
                    return new KDAMCHECK(course);
                }
                if (Opcode == 7) {
                    return new COURSESTAT(course);
                }
                if (Opcode == 9) {
                    return new ISREGISTER(course);
                }
                if ( Opcode == 10){
                    return new UNREGISTER(course);
                }
                bytes.clear();
                Opcode = 0;
            }
            if (Opcode == 8) {
                bytes.add(nextByte);
                if(nextByte == 0){
                    zeroByteNum++;
                }
                if(zeroByteNum == 1){
                    String username = DecodeIntoString(bytes.subList(2, bytes.indexOf(0)));
                    bytes.clear();
                    zeroByteNum = 0;
                    Opcode = 0;
                    return new STUDENTSTAT(username);
                }
            }
        }
        return null;
    }

    @Override
    public byte[] encode(Message message) {
        return message.encode();
    }

    private short bytesToShort(byte[] byteArr) {
        short result = (short) ((byteArr[0] & 0xff) << 8);
        result += (short) (byteArr[1] & 0xff);
        return result;
    }

    private String DecodeIntoString(List<Byte> lst){
        byte[] str = new byte[lst.size()];
        for (int i = 0; i < lst.size(); i++){
            str[i] = lst.get(i);
        }
        return new String(str, StandardCharsets.UTF_8);
    }
}
