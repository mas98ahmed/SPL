package bgu.spl.mics.application.services;

import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.BombDestroyerEvent;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.passiveObjects.Diary;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import java.util.concurrent.CountDownLatch;

/**
 * LandoMicroservice
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LandoMicroservice  extends MicroService {

    private long duration;
    private Diary diary = Diary.getInstance();
    private CountDownLatch latch;
    private Logger logger = LogManager.getLogger(LandoMicroservice.class);
    private long starting_time;

    public LandoMicroservice(long duration, CountDownLatch latch, long starting_time) {
        super("Lando");
        this.duration = duration;
        this.latch = latch;
        this.starting_time = starting_time;
    }

    @Override
    protected void initialize() {
        subscribeEvent(BombDestroyerEvent.class, msg -> {
            try {
                Thread.sleep(duration);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            complete(msg, true);
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setLandoTerminate(System.currentTimeMillis() - starting_time);
            terminate();
        });
        latch.countDown();
    }
}
