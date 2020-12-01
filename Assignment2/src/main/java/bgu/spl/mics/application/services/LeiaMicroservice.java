package bgu.spl.mics.application.services;

import java.util.ArrayList;
import java.util.List;

import bgu.spl.mics.*;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.*;
import com.sun.org.apache.xpath.internal.operations.Bool;;

/**
 * LeiaMicroservices Initialized with Attack objects, and sends them as  {@link AttackEvent}.
 * This class may not hold references for objects which it is not responsible for:
 * {@link AttackEvent}.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class LeiaMicroservice extends MicroService {

    private Attack[] attacks;

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
        while(finished == attacks.length) {
            for (int i = 0; i < futures.length; i++) {
                if (futures[i].get() == true) {
                    finished++;
                }
            }
        }
        //sending an event of deactivating the shield.
        Future<Boolean> deactivate = sendEvent(new DeactivationEvent());
        if(deactivate.isDone()) {
            //sending an event of bombing.
            Future<Boolean> bomb = sendEvent(new BombDestroyerEvent());
            if (bomb.isDone()) {
                //writing to the diary.
                sendBroadcast(new TerminateBroadcast());
                terminate();
            }
        }
    }
}
