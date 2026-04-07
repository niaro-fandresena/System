import threading
import time
import random

u = 1.0
compteur_iterations = 0
verrou = threading.Lock()

def f1(x):
    return (1/4) * (x - 1)**2

def f2(x):
    return (1/6) * (x - 2)**2

def thread_f1():
    global u, compteur_iterations
    while True:
        with verrou:
            compteur_iterations += 1
            u = f1(u)
            print(f"[T1] Itération {compteur_iterations} | u = {u:.6f}")
        
        time.sleep(random.randint(1, 5))

def thread_f2():
    global u, compteur_iterations
    while True:
        with verrou:
            compteur_iterations += 1
            u = f2(u)
            print(f"[T2] Itération {compteur_iterations} | u = {u:.6f}")
        
        time.sleep(random.randint(1, 5))

def main():
    t1 = threading.Thread(target=thread_f1, daemon=True)
    t2 = threading.Thread(target=thread_f2, daemon=True)

    print(f"Démarrage. Valeur initiale de u : {u}")

    t1.start()
    t2.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nArrêt du programme.")

if __name__ == "__main__":
    main()
