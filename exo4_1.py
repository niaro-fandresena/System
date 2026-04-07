import os
import sys

file_path = "test.txt"
t1_r, t1_w = os.pipe()
t2_r, t2_w = os.pipe()

fils = os.fork()

if fils == 0: # --- LE FILS ---
    os.close(t1_r)
    os.close(t2_w)
    
    word = input("Entrez le mot à chercher : ")
    os.write(t1_w, word.encode())
    res = os.read(t2_r, 1).decode()
    print(f"[Fils] Résultat reçu du père : {'Trouvé' if res == '1' else 'Non trouvé'}")
    
    os.close(t1_w)
    os.close(t2_r)

else: # --- LE PERE ---
    os.close(t1_w)
    os.close(t2_r)
    word_to_search = os.read(t1_r, 1024).decode()
    command = f"grep -q '{word_to_search}' {file_path}"
    status = os.system(command)
    
    if status == 0:
        os.write(t2_w, b"1")
    else:
        os.write(t2_w, b"0")
        
    os.close(t1_r)
    os.close(t2_w)
    os.wait() 
