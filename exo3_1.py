import sys

if len(sys.argv) == 3 and sys.argv[1] and sys.argv[2]:
    print(int(sys.argv[1]) + int (sys.argv[2]))
else:
    print("Arguments invalides ou insufiisants")
    sys.exit(1)
