package bgu.spl.mics.application.services;

import bgu.spl.mics.*;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.messages.FinishAttacks.*;
import bgu.spl.mics.application.passiveObjects.*;
;

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

    public LeiaMicroservice(Attack[] attacks) {
        super("Leia");
        this.attacks = attacks;
    }

    @Override
    protected void initialize() {
        Future<Boolean>[] futures = new Future[attacks.length];
        //sending the attacks.
        for (int i = 0; i < futures.length; i++) {
            futures[i] = sendEvent(new AttackEvent(attacks[i]));
        }
        //checking if all the attacks been finished.
        int finished = 0;
        while (finished == attacks.length) {
            for (int i = 0; i < futures.length; i++) {
                if (futures[i].isDone()) {
                    finished++;
                }
            }
        }
        sendEvent(new HanSoloFinishEvent());
        sendEvent(new C3POFinishEvent());
        //sending an event of deactivating the shield.
        Future<Boolean> R2D2DeactivateFuture = sendEvent(new DeactivationEvent());
        while (!R2D2DeactivateFuture.isDone()) ;
        //sending an event of bombing.
        Future<Boolean> bomb = sendEvent(new BombDestroyerEvent());
        while (!bomb.isDone()) ;
        diary.setLeiaTerminate(System.currentTimeMillis());
        sendBroadcast(new TerminateBroadcast());
        terminate();
    }
}
