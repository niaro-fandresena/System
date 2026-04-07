import threading

def afficher_tableau(tab):
    print(f"Tableau : {tab}")

def main():
    mon_tableau = [1, 2, 3, 4, 5]
    t = threading.Thread(target=afficher_tableau, args=(mon_tableau,))
    t.start()
    t.join()

if __name__ == "__main__":
    main()
