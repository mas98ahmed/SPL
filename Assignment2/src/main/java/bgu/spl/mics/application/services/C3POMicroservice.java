package bgu.spl.mics.application.services;

import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.C3POFinishEvent;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewoks;

import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * C3POMicroservices is in charge of the handling {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 * <p>
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class C3POMicroservice extends MicroService {

    private Ewoks ewoks = Ewoks.getInstance();
    private Diary diary = Diary.getInstance();
    private long Finishing_attacks_time = 0;

    public C3POMicroservice() {
        super("C3PO");
    }

    @Override
    protected void initialize() {
        subscribeEvent(AttackEvent.class, msg -> {
            List<Integer> serials = msg.getAttack().getSerials();
            if (ewoks.Acquire(serials)) {
                int duration = msg.getAttack().getDuration();
                ewoks.sendEwoks(serials, duration);
                diary.AddAttack();
                complete(msg, true);
                Finishing_attacks_time = System.currentTimeMillis();
            } else {
                complete(msg, null);
            }
        });

        subscribeEvent(C3POFinishEvent.class, msg -> diary.setC3POFinish(Finishing_attacks_time));

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setC3POTerminate(System.currentTimeMillis());
            terminate();
        });
    }
}
