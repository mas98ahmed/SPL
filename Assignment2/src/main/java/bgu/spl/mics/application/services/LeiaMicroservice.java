package bgu.spl.mics.application.services;

import bgu.spl.mics.*;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.*;
import bgu.spl.mics.application.passiveObjects.*;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;



/**
 * LeiaMicroservices Initialized with Attack objects, and sends them as  {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 * <p>
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LeiaMicroservice extends MicroService {

    private Attack[] attacks;
    private Diary diary = Diary.getInstance();
    private Logger logger = LogManager.getLogger(LeiaMicroservice.class);
    private long starting_time;

    public LeiaMicroservice(Attack[] attacks, long starting_time) {
        super("Leia");
        this.attacks = attacks;
        this.starting_time = starting_time;
    }

    @Override
    protected void initialize() {
        Future<Boolean>[] futures = new Future[attacks.length];
        //sending the attacks.
        for (int i = 0; i < futures.length; i++) {
            futures[i] = sendEvent(new AttackEvent(attacks[i]));
        }
       logger.info("all the attacks have been sent");
        //checking if all the attacks been finished.
        int finished = 0;
        while (finished != attacks.length) {
            for (int i = 0; i < futures.length; i++) {
                if (futures[i].isDone()) {
                    finished++;
                }
            }
        }
        logger.info("HanSolo and C3PO have finished");
        sendEvent(new HanSoloFinishEvent());
        sendEvent(new C3POFinishEvent());
        //sending an event of deactivating the shield.
        Future<Boolean> R2D2DeactivateFuture = sendEvent(new DeactivationEvent());
        boolean R2D2Finish = false;
        logger.info("R2D2 is starting now");
        while (!R2D2Finish) {
           if (R2D2DeactivateFuture.isDone()) {
                R2D2Finish = true;
            }
        }
        logger.info("R2D2 has finished");
        //sending an event of bombing.
        Future<Boolean> LandoFuture = sendEvent(new BombDestroyerEvent());
        logger.info("Lando is starting now");
        boolean LandoFinish = false;
        while(!LandoFinish) {
            if (LandoFuture.isDone()) {
                LandoFinish = true;
            }
        }
        logger.info("Lando has finished");
        sendBroadcast(new TerminateBroadcast());
        diary.setLeiaTerminate(System.currentTimeMillis() - starting_time);
        terminate();
    }
}
