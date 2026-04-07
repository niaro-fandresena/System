import threading
import random
import sys
import time

def generer(n):
    return [random.randint(0, 99) for _ in range(n)]

def inclusion(t1, t2):
    # Complexité : O(n1 * n2)
    for e in t1:
        if e not in t2:
            return 0
    return 1

def guetteur_annulation():
    while True:
        touche = sys.stdin.read(1)
        if touche.upper() == 'A':
            print("\n[Annulation] Touche A pressée. Fin.")
            sys.exit(0)

def main():
    t_annul = threading.Thread(target=guetteur_annulation, daemon=True)
    t_annul.start()

    res_t1 = []
    res_t2 = []

    def thread_t1(): res_t1.extend(generer(5))
    def thread_t2(): res_t2.extend(generer(10))

    st1 = threading.Thread(target=thread_t1)
    st2 = threading.Thread(target=thread_t2)

    st1.start()
    st2.start()
    st1.join()
    st2.join()

    print(f"T1: {res_t1}")
    print(f"T2: {res_t2}")

    res_inc = []
    def thread_inc(): res_inc.append(inclusion(res_t1, res_t2))
    
    si = threading.Thread(target=thread_inc)
    si.start()
    si.join()

    print(f"Inclusion : {'OUI' if res_inc[0] else 'NON'}")

if __name__ == "__main__":
    main()
