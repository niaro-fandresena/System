import threading
import time
import random
import sys

compt = 0
verrou = threading.Lock()

def thread_incrementeur(limite):
    global compt
    while True:
        with verrou:
            if compt >= limite:
                break
            compt += 1
            print(f"[Incrementeur] Compteur : {compt}")
        
        time.sleep(random.randint(1, 5))

def thread_afficheur(limite):
    global compt
    while True:
        with verrou:
            valeur_actuelle = compt
            if valeur_actuelle >= limite:
                break
        
        print(f"[Afficheur] Lecture : {valeur_actuelle}")
        time.sleep(2)

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <valeur_limite>")
        return

    limite = int(sys.argv[1])

    t1 = threading.Thread(target=thread_incrementeur, args=(limite,))
    t2 = threading.Thread(target=thread_afficheur, args=(limite,))

    t1.start()
    t2.start()

    t1.join()
    t2.join()
    print("Fin du programme.")

if __name__ == "__main__":
    main()
