

import sys
import os

while 1:
    dir = input("Entrez un nom de repértoire: ")
    if dir:
        command = "install -D ./* " + dir
        os.system(command)
    print()


