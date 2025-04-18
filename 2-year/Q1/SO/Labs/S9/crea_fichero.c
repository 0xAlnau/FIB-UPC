#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Nombre del fichero
    const char *filename = "salida.txt";

    // Permisos: lectura y escritura para el propietario
    mode_t permisos = S_IRUSR | S_IWUSR;

    int fd = creat(filename, permisos);
    if (fd == -1) {
        perror("Error al crear el fichero");
        return 1;
    }

    const char *content = "ABCD";
    ssize_t bytes_written = write(fd, content, strlen(content));

    if (bytes_written == -1) {
        perror("Error al escribir en el fichero");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("Error al cerrar el fichero");
        return 1;
    }

    printf("Fichero '%s' creado y escrito correctamente.\n", filename);
}
