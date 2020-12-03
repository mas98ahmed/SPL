package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.HanSoloFinishEvent;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewoks;
import java.util.*;
import java.util.concurrent.CountDownLatch;

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
    private Diary diary = Diary.getInstance();
    private CountDownLatch latch;

    public HanSoloMicroservice(CountDownLatch latch) {
        super("Han");
        this.latch = latch;
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
                }
                else {
                    ewoks.Release(serials);
                }
                diary.AddAttack();
            } else {
                complete(msg, null);
            }
        });

        subscribeEvent(HanSoloFinishEvent.class, msg -> diary.setHanSoloFinish(System.currentTimeMillis()));

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setHanSoloTerminate(System.currentTimeMillis());
            terminate();
        });
        latch.countDown();
    }
}
