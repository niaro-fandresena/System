import os
import sys
pid_f1 = os.fork()
if pid_f1 != 1:
    if pid_f1 == 0:
        print ("Fils 1")
    else:
        print ("Père")
        pid_f2 = os.fork()
        if pid_f2 != -1:
            print ("Fils 2" if pid_f2 == 0 else "Père")
        else:
            print ("Erreur(création du fils2)")
else:
    print("Erreur(crétion du fils1)")

    
