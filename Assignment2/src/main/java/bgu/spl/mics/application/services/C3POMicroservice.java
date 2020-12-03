package bgu.spl.mics.application.services;

import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.C3POFinishEvent;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewoks;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;


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

    public C3POMicroservice() {
        super("C3PO");
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
                if (duration > 0) {
                    ewoks.sendEwoks(serials, duration);
                } else {
                    ewoks.Release(serials);
                }
                diary.AddAttack();
            } else {
                complete(msg, null);
            }
        });

        subscribeEvent(C3POFinishEvent.class, msg -> diary.setC3POFinish(System.currentTimeMillis()));

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setC3POTerminate(System.currentTimeMillis());
            terminate();
        });
    }
}
