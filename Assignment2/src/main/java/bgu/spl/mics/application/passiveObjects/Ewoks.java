package bgu.spl.mics.application.passiveObjects;

import java.util.*;

/**
 * Passive object representing the resource manager.
 * <p>
 * This class must be implemented as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private methods and fields to this class.
 */
public class Ewoks {

    private static Ewoks instance = null;
    private Map<Integer, Ewok> ewoks = new HashMap();

    public static Ewoks getInstance() {
        if (instance == null) {
            instance = new Ewoks();
        }
        return instance;
    }

    public synchronized void load(Ewok[] ewoks) {
        for (Ewok ewok : ewoks) {
            this.ewoks.put(ewok.getSerialNumber(), ewok);
        }
    }

    public synchronized void Release(List<Integer> serials){
        for (Integer serial : serials) {
            if (ewoks.containsKey(serial))
                ewoks.get(serial).release();
        }
        notify();
    }

    public synchronized boolean Acquire(List<Integer> serials){
        Collections.sort(serials);
        for (Integer serial : serials) {
            if (!ewoks.containsKey(serial)) {
                return false;
            }
        }
        for (Integer s : serials) {
            while (!ewoks.get(s).isAvailable()) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            ewoks.get(s).acquire();
        }
        return true;
    }

    public synchronized void sendEwoks(List<Integer> serials, int time) {
        for (Integer serial : serials) {
            if (!ewoks.containsKey(serial)) {
                return;
            }
        }
        try {
            Thread.sleep(time * 100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Release(serials);
    }
}
