import threading
import time
import random
sem1 = threading.Semaphore(0)
sem2 = threading.Semaphore(0)

def thread_t1():
    for i in range(1, 11):
        print(f"[T1] Itération {i} : Traitement (2s)...")
        time.sleep(2)
        
        print(f"[T1] Arrivé au rendez-vous {i}. Attend T2...")
        sem1.release() 
        sem2.acquire()
        print(f"[T1] Rendez-vous {i} terminé. On continue.\n")

def thread_t2():
    for i in range(1, 11):
        duree = random.randint(4, 9)
        print(f"[T2] Itération {i} : Traitement ({duree}s)...")
        time.sleep(duree)
        
        print(f"[T2] Arrivé au rendez-vous {i}. Attend T1...")
        sem2.release()
        sem1.acquire()
        print(f"[T2] Rendez-vous {i} terminé. On continue.\n")

def main_a():
    t1 = threading.Thread(target=thread_t1)
    t2 = threading.Thread(target=thread_t2)
    t1.start()
    t2.start()
    t1.join()
    t2.join()

if __name__ == "__main__":
    main_a()
