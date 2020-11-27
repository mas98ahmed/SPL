package bgu.spl.mics;

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
    }

    @Test
    void registerTest() {
        Assertions.assertDoesNotThrow(()->{ m.register(s); });
        Assertions.assertDoesNotThrow(()->{ m.register(s1); });
    }

    @Test
    void unregisterTest() {
        Assertions.assertDoesNotThrow(()->{m.unregister(s1);});
        Assertions.assertDoesNotThrow(()->{m.unregister(null);});
    }

    @Test
    void awaitMessageTest() {
        m.register(s);
        Event<String> msg = new Event<String>() {};
        s.sendEvent(msg);
        Assertions.assertDoesNotThrow(()->{ m.awaitMessage(s); });
        Assertions.assertThrows(InterruptedException.class, ()->{ m.awaitMessage(s1); });
        m.unregister(s);
    }

    @Test
    void complete() {
        m.register(s);
        Event<String> msg = new Event<String>() {};
        Future<String> f =s.sendEvent(msg);
        m.complete(msg,"Ahmed");
        Assertions.assertEquals(f.get(3, TimeUnit.SECONDS),"Ahmed");
        m.unregister(s);
    }
}