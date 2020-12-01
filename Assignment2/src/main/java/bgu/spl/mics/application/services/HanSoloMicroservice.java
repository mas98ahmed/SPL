package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Ewoks;
import java.util.*;

/**
 * HanSoloMicroservices is in charge of the handling {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class HanSoloMicroservice extends MicroService {

    private Ewoks ewoks = Ewoks.getInstance();

    public HanSoloMicroservice() {
        super("Han");
    }

    @Override
    protected void initialize() {
        subscribeEvent(AttackEvent.class, msg -> {
            List<Integer> serials = msg.getAttack().getSerials();
            if (ewoks.Acquire(serials)) {
                int duration = msg.getAttack().getDuration();
                try {
                    Thread.sleep(duration * 100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                complete(msg, true);
                if (duration > 0)
                    ewoks.sendEwoks(serials, duration);
                else
                    ewoks.Release(serials);
            } else {
                complete(msg, null);
            }
        });

        subscribeBroadcast(TerminateBroadcast.class, msg -> terminate());
    }
}
