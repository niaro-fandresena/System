import os
import sys
nb_proc = 5
for i in range(nb_proc):
    pid_f = os.fork()
    if pid_f != -1:
        if pid_f == 0:
            print("Fils")
            break
        else:
            print("Père")
    else:
        print("Erreur(création du fils)")
