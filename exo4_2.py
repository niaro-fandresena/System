import os
import sys

def main():
    r, w = os.pipe()

    fils = os.fork()

    if fils == 0:
        os.close(w)
        os.dup2(r, sys.stdin.fileno())
        os.close(r)
        donnee = sys.stdin.read()
        print(f"\n[Fils] J'ai reçu via mon stdin redirigé : {donnee}")
        
    else:
        os.close(r)
        os.dup2(w, sys.stdout.fileno())
        os.close(w)
        print("Ceci est un message envoyé depuis le stdout du père.")
        sys.stdout.flush()
        os.close(sys.stdout.fileno())
        os.wait()

if __name__ == "__main__":
    main()
