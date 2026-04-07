

import sys
import os

file = input("Entrez le nom du ficher à modifier: ")
os.execl("/usr/bin/emacs", "emacs", file)


