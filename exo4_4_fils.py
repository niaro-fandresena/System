import os
import sys
r_str = os.environ.get("TUBE_R")

if r_str:
    r = int(r_str)
    donnee = os.read(r, 1024).decode()
    print(f"[Fils] Lu depuis le tube (FD {r}) : {donnee}")
    os.close(r)
else:
    print("Erreur : Variable TUBE_R non trouvée")
