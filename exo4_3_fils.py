import os
import sys

if len(sys.argv) < 2:
    sys.exit(1)
r = int(sys.argv[1])
donnee = os.read(r, 1024).decode()

print(f"[Programme Fils Executé] Message reçu : {donnee}")
os.close(r)
