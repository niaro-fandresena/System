#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    for (int i = 1; i < argc; i++) { 
        DIR *dir = opendir(argv[i]);
        if (!dir) continue;

        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            struct stat st;
            char name[1024];
            sprintf(name, "%s/%s", argv[i], ent->d_name);

            if (stat(name, &st) == 0) {
                if (S_ISREG(st.st_mode) && st.st_size >= 1000000) {
                    printf("Fichier: %s | Taille: %ld octets | UID: %d\n", 
                            ent->d_name, (long)st.st_size, st.st_uid);
                }
            }
        }
        closedir(dir);
    }
    return 0;
}
