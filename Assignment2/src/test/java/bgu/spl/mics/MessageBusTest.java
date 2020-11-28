package bgu.spl.mics;

import bgu.spl.mics.application.messages.AttackEvent;
import bgu.spl.mics.application.passiveObjects.Attack;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.concurrent.TimeUnit;

class MessageBusTest {

    MessageBusImpl m;
    MicroService s;
    MicroService s1;

    @BeforeEach
    public void setUp() {
        m =  MessageBusImpl.getInstance();
        s = new MicroService("Ahmed") {
            @Override
            protected void initialize() {}
        };

        s1 = new MicroService("Dan") {
            @Override
            protected void initialize() {}
        };
        m.register(s);
        m.register(s1);
    }

    @Test
    void registerTest() {
        Assertions.assertDoesNotThrow(()->{ m.register(s); });
        Assertions.assertDoesNotThrow(()->{ m.register(s1); });
    }

    @Test
    void unregisterTest() {
        Assertions.assertDoesNotThrow(()->{m.unregister(s1);});
    }

    @Test
    void awaitMessageTest() {
        AttackEvent msg = new AttackEvent();
        m.subscribeEvent(AttackEvent.class,s1);
        s.sendEvent(msg);
        Assertions.assertDoesNotThrow(()->{ m.awaitMessage(s1); });
    }

    @Test
    void complete() {
        Event msg = new AttackEvent();
        m.subscribeEvent(AttackEvent.class,s1);
        Future<String> f =s.sendEvent(msg);
        m.complete(msg,true);
        Assertions.assertEquals(f.get(3, TimeUnit.SECONDS),true);
    }

    @Test
    void subscribeBroadcastTest() {
        Broadcast msg = new Broadcast() {};
        m.subscribeBroadcast(msg.getClass(),s1);
        s.sendBroadcast(msg);
        Message massage = m.awaitMessage(s1);
        Assertions.assertEquals(massage.getClass(),msg.getClass());
    }

    @Test
    void subscribeEventTest() {
        AttackEvent msg = new AttackEvent();
        m.subscribeEvent(msg.getClass(),s1);
        s.sendEvent(msg);
        Message massage = m.awaitMessage(s1);
        Assertions.assertEquals(massage.getClass(),msg.getClass());
    }

    @Test
    void sendBroadcastTest() {
        Broadcast msg = new Broadcast() {};
        m.subscribeBroadcast(msg.getClass(),s1);
        s.sendBroadcast(msg);
        Assertions.assertEquals(m.awaitMessage(s1),msg);
    }

    @Test
    void sendEventTest() {
        AttackEvent msg = new AttackEvent();
        m.subscribeEvent(msg.getClass(),s1);
        s.sendEvent(msg);
        Assertions.assertEquals(m.awaitMessage(s1),msg);
    }
}