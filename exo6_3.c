#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int n, i;
    printf("Nombre d'entiers ? "); 
    scanf("%d", &n);
    int tab[n];
    for(i=0; i<n; i++) scanf("%d", &tab[i]);

    int fd = open("tableau.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, tab, sizeof(int) * n);
    close(fd);
    return 0;
}
