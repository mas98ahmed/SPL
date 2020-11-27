package bgu.spl.mics;

import bgu.spl.mics.application.passiveObjects.Ewok;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class EwokTest {

    Ewok ewok;

    @BeforeEach
    void setUp() {
        ewok = new Ewok(1);
    }

    @Test
    void acquire() {
        assertTrue(ewok.isAvailable());
        ewok.acquire();
        assertFalse(ewok.isAvailable());
    }

    @Test
    void release() {
        assertFalse(ewok.isAvailable());
        ewok.acquire();
        assertTrue(ewok.isAvailable());
    }
}