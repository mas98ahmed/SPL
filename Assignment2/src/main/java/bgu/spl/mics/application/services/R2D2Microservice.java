package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Diary;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import java.util.concurrent.CountDownLatch;

/**
 * R2D2Microservices is in charge of the handling {@link DeactivationEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link DeactivationEvent}.
 * <p>
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class R2D2Microservice extends MicroService {

    private long duration;
    private Diary diary = Diary.getInstance();
    private CountDownLatch latch;
    private Logger logger = LogManager.getLogger(R2D2Microservice.class);
    private long starting_time;

    public R2D2Microservice(long duration, CountDownLatch latch, long starting_time) {
        super("R2D2");
        this.duration = duration;
        this.latch = latch;
        this.starting_time = starting_time;
    }

    @Override
    protected void initialize() {
        subscribeEvent(DeactivationEvent.class, msg -> {
            try {
                Thread.sleep(duration);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            diary.setR2D2Deactivate(System.currentTimeMillis() - starting_time);
            complete(msg, true);
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setR2D2Terminate(System.currentTimeMillis() - starting_time);
            terminate();

        });
        latch.countDown();
    }
}
