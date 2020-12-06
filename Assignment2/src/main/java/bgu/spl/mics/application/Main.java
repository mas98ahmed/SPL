package bgu.spl.mics.application;

import bgu.spl.mics.application.passiveObjects.Attack;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Ewok;
import bgu.spl.mics.application.passiveObjects.Ewoks;
import bgu.spl.mics.application.services.*;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.util.*;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.CountDownLatch;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * This is the Main class of the application. You should parse the input file,
 * create the different components of the application, and run the system.
 * In the end, you should output a JSON.
 */
public class Main {
    public static void main(String[] args) {
        Logger logger = LogManager.getLogger(Main.class);
        JsonParser parser = new JsonParser();
        try (FileReader fileReader = new FileReader(args[0])) {
            Object obj = parser.parse(fileReader);
            JsonObject jsonobject = (JsonObject) obj;
            JsonArray attacks = jsonobject.get("attacks").getAsJsonArray();
            long r2d2_duration = jsonobject.get("R2D2").getAsLong();
            long lando_duration = jsonobject.get("Lando").getAsLong();
            int ewoks_num = jsonobject.get("Ewoks").getAsInt();
            Ewoks ewoks = Ewoks.getInstance();
            ewoks.load(Ewoks(ewoks_num));
            CountDownLatch latch = new CountDownLatch(4);
            long starting_time = System.currentTimeMillis();
            List<Thread> threads = new LinkedList<>();
            threads.add(new Thread(new HanSoloMicroservice(latch, starting_time)));
            threads.add(new Thread(new C3POMicroservice(latch, starting_time)));
            threads.add(new Thread(new R2D2Microservice(r2d2_duration, latch, starting_time)));
            threads.add(new Thread(new LandoMicroservice(lando_duration, latch, starting_time)));
            for (Thread thread : threads) {
                thread.start();
            }
            try {
                latch.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            try {
                Thread Leia = new Thread(new LeiaMicroservice(Attacks(attacks), starting_time));
                Leia.start();
                Leia.join();
                for (Thread thread : threads) {
                    thread.join();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Diary diary = Diary.getInstance();
            diary.printToFile(args[1]);
        } catch (IOException e) {
            e.printStackTrace();
        }
        logger.info("finish all the program");
    }

    private static Attack[] Attacks(JsonArray atks) {
        Attack[] attacks = new Attack[atks.size()];
        for (int i = 0; i < atks.size(); i++) {
            JsonObject attack = atks.get(i).getAsJsonObject();
            int duration = attack.get("duration").getAsInt();
            List<Integer> ewoks = new LinkedList<>();
            JsonArray ewk = attack.get("serials").getAsJsonArray();
            for (int j = 0; j < ewk.size(); j++) {
                ewoks.add(ewk.get(j).getAsInt());
            }
            attacks[i] = new Attack(ewoks, duration);
        }
        return attacks;
    }

    private static Ewok[] Ewoks(int ewoks_num) {
        Ewok[] ewoks = new Ewok[ewoks_num];
        for (int i = 0; i < ewoks_num; i++) {
            ewoks[i] = new Ewok(i + 1);
        }
        return ewoks;
    }
}
