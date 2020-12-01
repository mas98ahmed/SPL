package bgu.spl.mics.application.services;

import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.DeactivationEvent;
import bgu.spl.mics.application.messages.TerminateBroadcast;

/**
 * LandoMicroservice
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LandoMicroservice  extends MicroService {

    private long duration;

    public LandoMicroservice(long duration) {
        super("Lando");
        this.duration = duration;
    }

    @Override
    protected void initialize() {
        subscribeEvent(DeactivationEvent.class, msg -> {
            try {
                Thread.sleep(duration * 100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            complete(msg, true);
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> terminate());
    }
}
