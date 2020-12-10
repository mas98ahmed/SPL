package bgu.spl.mics.application.services;


import bgu.spl.mics.MicroService;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.HanSoloFinishEvent;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewoks;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import java.util.*;
import java.util.concurrent.CountDownLatch;

/**
 * HanSoloMicroservices is in charge of the handling {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 * <p>
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class HanSoloMicroservice extends MicroService {

    private Ewoks ewoks = Ewoks.getInstance();
    private Diary diary = Diary.getInstance();
    private CountDownLatch latch;
   // private Logger logger = LogManager.getLogger(HanSoloMicroservice.class);
    private long Finishing_attacks_time = 0;

    public HanSoloMicroservice(CountDownLatch latch) {
        super("Han");
        this.latch = latch;
    }

    @Override
    protected void initialize() {
        subscribeEvent(AttackEvent.class, msg -> {
            List<Integer> serials = msg.getAttack().getSerials();
           // logger.info("HanSolo started");
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

        subscribeEvent(HanSoloFinishEvent.class, msg -> diary.setHanSoloFinish(Finishing_attacks_time));

        subscribeBroadcast(TerminateBroadcast.class, msg -> {
            diary.setHanSoloTerminate(System.currentTimeMillis());
            terminate();
        });
        latch.countDown();
    }
}
