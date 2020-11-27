package bgu.spl.mics;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * The {@link MessageBusImpl class is the implementation of the MessageBus interface.
 * Write your implementation here!
 * Only private fields and methods can be added to this class.
 */
public class MessageBusImpl implements MessageBus {

    private static MessageBusImpl instance = null;
    private ConcurrentHashMap<MicroService, LinkedBlockingQueue<Message>> micros = new ConcurrentHashMap<>();
    private ConcurrentHashMap<Event, Future> future_events = new ConcurrentHashMap<>();
    private ConcurrentHashMap<Class<? extends Event>, ConcurrentLinkedQueue<MicroService>> topic_event = new ConcurrentHashMap<>();
    private ConcurrentHashMap<Class<? extends Broadcast>, ConcurrentLinkedQueue<MicroService>> topic_broad = new ConcurrentHashMap<>();
    private ConcurrentHashMap<MicroService, ConcurrentLinkedQueue<Class<? extends Event>>> micros_event_type = new ConcurrentHashMap<>();
    private ConcurrentHashMap<MicroService, ConcurrentLinkedQueue<Class<? extends Broadcast>>> micros_broad_type = new ConcurrentHashMap<>();

    public static MessageBusImpl getInstance(){
        if(instance == null){
            instance = new MessageBusImpl();
        }
        return instance;
    }

    @Override
    public <T> void subscribeEvent(Class<? extends Event<T>> type, MicroService m) {
        topic_event.putIfAbsent(type, new ConcurrentLinkedQueue<>());
        micros_event_type.putIfAbsent(m, new ConcurrentLinkedQueue<Class<? extends Event>>());
        synchronized (m) {
            ConcurrentLinkedQueue<Class<? extends Event>> q = micros_event_type.get(m);
            if (q == null) {
                return;
            }
            q.add(type);
        }
        synchronized (type) {
            ConcurrentLinkedQueue<MicroService> q2 = topic_event.get(type);
            if (q2 != null)
                q2.add(m);
        }
    }

    @Override
    public void subscribeBroadcast(Class<? extends Broadcast> type, MicroService m) {
        topic_broad.putIfAbsent(type, new ConcurrentLinkedQueue<>());
        micros_broad_type.putIfAbsent(m, new ConcurrentLinkedQueue<>());
        synchronized (m) {
            ConcurrentLinkedQueue<Class<? extends Broadcast>> q = micros_broad_type.get(m);
            if (q == null) {
                return;
            }
            q.add(type);
        }
        synchronized (type) {
            ConcurrentLinkedQueue<MicroService> q2 = topic_broad.get(type);
            if (q2 == null)
                return;
            q2.add(m);
        }
    }

    @Override
    @SuppressWarnings("unchecked")
    public <T> void complete(Event<T> e, T result) {
        future_events.get(e).resolve(result);
    }

    @Override
    public void sendBroadcast(Broadcast b) {
        synchronized (b.getClass()) {
            if (topic_broad.containsKey(b.getClass())) {
                ConcurrentLinkedQueue<MicroService> micro = topic_broad.get(b.getClass());
                for (MicroService m : micro) {
                    LinkedBlockingQueue<Message> q = micros.get(m);
                    if (q != null) {
                        q.add(b);
                    }
                }
            }
        }
    }


    @Override
    public <T> Future<T> sendEvent(Event<T> e) {
        MicroService m;
        Future<T> future = new Future<>();
        synchronized (e.getClass()) {
            if (topic_event.get(e.getClass()) == null || !topic_event.containsKey(e.getClass())) {
                return null;
            }
            future_events.put(e, future);
            ConcurrentLinkedQueue<MicroService> queue = topic_event.get(e.getClass());
            if (queue == null) {//if no queue then no one has registered to it yet, or already unregistered
                return null;
            }
            m = queue.poll();
            if (m == null) {
                return null;
            }
            queue.add(m);
        }

        synchronized (m) {
            LinkedBlockingQueue<Message> q2 = micros.get(m);
            if (q2 == null) {
                return null;
            }
            q2.add(e);
        }
        return future;
    }

    @Override
    public void register(MicroService m) {
        micros.putIfAbsent(m, new LinkedBlockingQueue<>());
    }

    @Override
    public void unregister(MicroService m) {
        if (micros.containsKey(m)) {
            LinkedBlockingQueue<Message> q;

            if (micros_event_type.containsKey(m)) {
                ConcurrentLinkedQueue<Class<? extends Event>> q3 = micros_event_type.get(m);
                for (Class<? extends Event> type : q3) {
                    synchronized (type) {
                        topic_event.get(type).remove(m);
                    }
                }
                micros_event_type.remove(m);
            }
            synchronized (m) {
                if (micros_broad_type.containsKey(m)) {
                    ConcurrentLinkedQueue<Class<? extends Broadcast>> q2 = micros_broad_type.get(m);
                    for (Class<? extends Broadcast> type : q2) {
                        synchronized (type) {
                            topic_broad.get(type).remove(m);
                        }
                    }
                    micros_broad_type.remove(m);
                }
                q = micros.remove(m);
                if (q == null) {
                    return;
                }
            }
            while (!q.isEmpty()) {
                Message message = q.poll();
                if (message != null) {
                    Future<?> future = future_events.get(message);
                    if (future != null) {
                        future.resolve(null);
                    }
                }
            }
        }
    }

    @Override
    public Message awaitMessage(MicroService m) {
        LinkedBlockingQueue<Message> q = micros.get(m);
        if (q == null) {
            throw new IllegalArgumentException("MicroService is not registered");
        }
        Message msg = null;
        synchronized (q){
            try {
                msg = q.take();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        return msg;
    }
}
