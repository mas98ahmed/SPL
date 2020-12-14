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
            //Saving the Data of the input file.
            JsonArray attacks = jsonobject.get("attacks").getAsJsonArray();
            long r2d2_duration = jsonobject.get("R2D2").getAsLong();
            long lando_duration = jsonobject.get("Lando").getAsLong();
            int ewoks_num = jsonobject.get("Ewoks").getAsInt();
            Ewoks ewoks = Ewoks.getInstance();
            ewoks.load(Ewoks(ewoks_num));
            //=====================================================================
            //The Microservices
            HanSoloMicroservice HanSolo = new HanSoloMicroservice();
            C3POMicroservice C3PO = new C3POMicroservice();
            R2D2Microservice R2D2 = new R2D2Microservice(r2d2_duration);
            LandoMicroservice Lando = new LandoMicroservice(lando_duration);
            //=====================================================================
            //Threads.
            List<Thread> threads = new LinkedList<>();
            threads.add(new Thread(HanSolo));
            threads.add(new Thread(C3PO));
            threads.add(new Thread(R2D2));
            threads.add(new Thread(Lando));
            //Running the threads.
            for (Thread thread : threads) {
                thread.start();
            }
            try {
                //sleep the main for a while to let the other threads that we've defined to subscribe.
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            try {
                Thread Leia = new Thread(new LeiaMicroservice(Attacks(attacks)));
                Leia.start();
                Leia.join();
                for (Thread thread : threads) {
                    thread.join();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }//printing to the diary
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
