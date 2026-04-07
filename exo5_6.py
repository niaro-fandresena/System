import threading
import time
import random

N = 100
tableau = [random.uniform(0, 100) for _ in range(N)]
tableau[0] = 0.0
tableau[99] = 0.0

verrou = threading.Lock()

def thread_moyenne():
    global tableau
    while True:
        with verrou:
            nouveau_tab = list(tableau)
            for i in range(1, 99):
                nouveau_tab[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3
            tableau = nouveau_tab
            print("\n[Moyenne] Calcul terminé.")
            
        time.sleep(random.randint(1, 3))

def thread_afficheur():
    while True:
        time.sleep(4)
        with verrou:
            print("\n--- État du tableau ---")
            print([round(x, 2) for x in tableau])

def main():
    t1 = threading.Thread(target=thread_moyenne, daemon=True)
    t2 = threading.Thread(target=thread_afficheur, daemon=True)

    t1.start()
    t2.start()

    # Le programme principal attend indéfiniment
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nArrêt du programme.")

if __name__ == "__main__":
    main()
