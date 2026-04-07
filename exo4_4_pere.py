import os
import sys

r, w = os.pipe()
fils = os.fork()

if fils == 0:
    os.close(w)
    os.environ["TUBE_R"] = str(r)
    
    path = os.path.abspath("fils.py")
    os.execvpe(sys.executable, [sys.executable, path], os.environ)
else:
    os.close(r)
    os.write(w, b"Message via environnement")
    os.close(w)
    os.wait()
