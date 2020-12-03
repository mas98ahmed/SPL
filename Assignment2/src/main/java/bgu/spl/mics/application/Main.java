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
import java.util.LinkedList;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * This is the Main class of the application. You should parse the input file,
 * create the different components of the application, and run the system.
 * In the end, you should output a JSON.
 */
public class Main {
    public static void main(String[] args) {
        JsonParser parser = new JsonParser();
        try (FileReader fileReader = new FileReader(args[0])) {
            Object obj = parser.parse(fileReader);
            JsonObject jsonobject = (JsonObject) obj;
            JsonArray attacks = jsonobject.get("attacks").getAsJsonArray();
            long r2d2_duration = jsonobject.get("R2D2").getAsLong();
            long lando_duration = jsonobject.get("Lando").getAsLong();
            int ewoks_num = jsonobject.get("Ewoks").getAsInt();
            CountDownLatch latch = new CountDownLatch(5);
            Thread Leia = new Thread(new LeiaMicroservice(Attacks(attacks), latch));
            Thread HanSolo = new Thread(new HanSoloMicroservice(latch));
            Thread C3PO = new Thread(new C3POMicroservice(latch));
            Thread R2D2 = new Thread(new R2D2Microservice(r2d2_duration, latch));
            Thread Lando = new Thread(new LandoMicroservice(lando_duration, latch));
            Ewoks ewoks = Ewoks.getInstance();
            ewoks.load(Ewoks(ewoks_num));
            ExecutorService executor = Executors.newFixedThreadPool(5);
            executor.submit(Leia);
            executor.submit(HanSolo);
            executor.submit(C3PO);
            executor.submit(R2D2);
            executor.submit(Lando);
            try {
                latch.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Diary diary = Diary.getInstance();
            diary.printToFile(args[1]);
        } catch (IOException e) {
            e.printStackTrace();
        }

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
