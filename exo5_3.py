import threading
import random

class TypeTableau:
    def __init__(self):
        self.tableau = []
        self.nb_elements = 0
        self.x = 0

def generer_type_tableau(obj, n):
    obj.nb_elements = n
    obj.tableau = [random.randint(0, 99) for _ in range(n)]

def chercher_element(obj):
    return 1 if obj.x in obj.tableau else 0

def main():
    data = TypeTableau()
    n = int(input("Nombre d'éléments : "))
    
    t_gen = threading.Thread(target=generer_type_tableau, args=(data, n))
    t_gen.start()
    
    data.x = int(input("Entrez l'entier x à chercher : "))
    
    t_gen.join()
    
    resultat = []
    def wrapper():
        resultat.append(chercher_element(data))
        
    t_search = threading.Thread(target=wrapper)
    t_search.start()
    t_search.join()
    
    print(f"Présence de {data.x} : {resultat[0]}")

if __name__ == "__main__":
    main()
