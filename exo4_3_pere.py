import os
import sys

r, w = os.pipe()
fils = os.fork()

if fils == 0:
    os.close(w)
    # Transmission du descripteur de lecture 'r' en argument
    path = os.path.abspath("fils.py")
    os.execv(sys.executable, [sys.executable, path, str(r)])
else:
    os.close(r)
    message = b"Message secret du pere"
    os.write(w, message)
    os.close(w)
    os.wait()
