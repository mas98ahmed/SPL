package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Diary;
import java.util.concurrent.CountDownLatch;

import static java.lang.Thread.sleep;

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


    public R2D2Microservice(long duration, CountDownLatch latch) {
        super("R2D2");
        this.duration = duration;
        this.latch = latch;
    }

    @Override
    protected void initialize() {
        subscribeEvent(DeactivationEvent.class, msg -> {
            try {
                sleep(duration);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            diary.setR2D2Deactivate(System.currentTimeMillis());
            complete(msg, true);
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setR2D2Terminate(System.currentTimeMillis());
            terminate();
        });
        latch.countDown();
    }
}
