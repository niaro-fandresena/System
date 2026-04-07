import threading
import random

class ThreadTableau(threading.Thread):
    def __init__(self, n):
        super().__init__()
        self.n = n
        self.resultat = None

    def run(self):
        self.resultat = [random.randint(0, 99) for _ in range(self.n)]

def main():
    t = ThreadTableau(10)
    t.start()
    t.join()
    print(f"Tableau généré : {t.resultat}")

if __name__ == "__main__":
    main()
