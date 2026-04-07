

import os

while 1:
    file = input("Entrez un nom de fichier: ")
    if file:
        fils = os.fork()
        if fils == 0:
            os.execl("/usr/bin/emacs", "emacs", file)
    print()


