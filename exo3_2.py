import sys
import os

if sys.argv[1]:
    command = "install -D./* " + sys.argv[1]
    os.system(command)
