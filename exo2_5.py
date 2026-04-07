import os
import sys
import time
import random
debut = time.time()
rand1 = random.randint(1, 10)
rand2 = random.randint(1, 10)
pid_f1 = os.fork()
if pid_f1 == 0:
    time.sleep(rand1)
    print("Fils 1: ", time.time() - debut)
else:
    pid_f2 = os.fork()
    if pid_f2 == 0:
        time.sleep(rand2)
        print("Fils 2: ", time.time() - debut)
    else:
        os.wait()
    os.wait()
