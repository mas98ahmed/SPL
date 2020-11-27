package bgu.spl.mics;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.concurrent.TimeUnit;
import static org.junit.jupiter.api.Assertions.*;


public class FutureTest {

    private Future<String> future;

    @BeforeEach
    public void setUp() {
        future = new Future<>();
    }

    @Test
    public void testResolve() {
        String str = "someResult";
        future.resolve(str);
        assertTrue(future.isDone());
        assertEquals(future.get(), str);
    }

    @Test
    public void testget() {
        String name = "Ahmed";
        assertFalse(future.isDone());
        String future_name = future.get(3, TimeUnit.SECONDS);
        assertNull(future_name);
        future.resolve(name);
        future_name = future.get(3, TimeUnit.SECONDS);
        if (future.isDone())
            assertSame("Ahmed", future_name);
        if (!future.isDone())
            assertNull(future_name);
    }

    @Test
    public void testIsDone() {
        String name = "Dan";
        assertTrue(future.isDone() == false);
        future.resolve(name);
        assertTrue(future.isDone() == true);
    }
}
