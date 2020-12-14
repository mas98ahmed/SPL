package bgu.spl.mics.application.services;

import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.BombDestroyerEvent;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.passiveObjects.Diary;

import java.util.concurrent.CountDownLatch;

import static java.lang.Thread.sleep;

/**
 * LandoMicroservice
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LandoMicroservice extends MicroService {

    private long duration;
    private Diary diary = Diary.getInstance();


    public LandoMicroservice(long duration) {
        super("Lando");
        this.duration = duration;
    }

    @Override
    protected void initialize() {
        subscribeEvent(BombDestroyerEvent.class, msg -> {
            try {
                sleep(duration);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            complete(msg, true);
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setLandoTerminate(System.currentTimeMillis());
            terminate();
        });
    }
}
