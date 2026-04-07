import threading
import time
import random

BAL = None

sem_vide = threading.Semaphore(1) 
sem_plein = threading.Semaphore(0)

def thread_emetteur():
    global BAL
    for i in range(65, 75):
        octet = chr(i)
        
        sem_vide.acquire()
        
        BAL = octet
        print(f"[Émetteur] Octet '{octet}' déposé.")
        
        sem_plein.release()
        
        time.sleep(random.randint(1, 3))

def thread_recepteur():
    global BAL
    for _ in range(10):
        sem_plein.acquire()
        
        lecture = BAL
        print(f"[Récepteur] Octet '{lecture}' lu.")
        
        sem_vide.release()
        
        time.sleep(random.randint(1, 3))

def main():
    te = threading.Thread(target=thread_emetteur)
    tr = threading.Thread(target=thread_recepteur)
    
    print("Démarrage du transfert...\n")
    te.start()
    tr.start()
    
    te.join()
    tr.join()
    print("\nTransfert terminé sans perte ni doublon.")

if __name__ == "__main__":
    main()
