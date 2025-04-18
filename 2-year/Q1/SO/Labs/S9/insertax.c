#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *filename = "salida.txt";

    // Abrir el fichero para lectura y escritura
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error al abrir el fichero");
        return 1;
    }

    // Determinar el tamaño del fichero
    off_t filesize = lseek(fd, 0, SEEK_END);
    if (filesize == -1) {
        perror("Error al obtener el tamaño del fichero");
        close(fd);
        return 1;
    }

    if (filesize < 2) {
        fprintf(stderr, "El fichero es demasiado pequeño para insertar 'X'.\n");
        close(fd);
        return 1;
    }

    // Leer todo el contenido del fichero en memoria
    char *buffer = malloc(filesize);
    if (!buffer) {
        perror("Error al asignar memoria");
        close(fd);
        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error al mover el cursor al inicio del fichero");
        free(buffer);
        close(fd);
        return 1;
    }

    if (read(fd, buffer, filesize) != filesize) {
        perror("Error al leer el contenido del fichero");
        free(buffer);
        close(fd);
        return 1;
    }

    // Crear un nuevo buffer con espacio para 'X'
    char *new_buffer = malloc(filesize + 1);
    if (!new_buffer) {
        perror("Error al asignar memoria para el nuevo buffer");
        free(buffer);
        close(fd);
        return 1;
    }

    // Copiar los datos al nuevo buffer e insertar 'X'
    memcpy(new_buffer, buffer, filesize - 1); // Copiar hasta el penúltimo carácter
    new_buffer[filesize - 1] = 'X';          // Insertar 'X'
    new_buffer[filesize] = buffer[filesize - 1]; // Copiar el último carácter

    // Escribir el nuevo contenido al fichero
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error al mover el cursor al inicio del fichero");
        free(buffer);
        free(new_buffer);
        close(fd);
        return 1;
    }

    if (write(fd, new_buffer, filesize + 1) != filesize + 1) {
        perror("Error al escribir el contenido actualizado");
        free(buffer);
        free(new_buffer);
        close(fd);
        return 1;
    }

    // Truncar el fichero para el nuevo tamaño
    if (ftruncate(fd, filesize + 1) == -1) {
        perror("Error al truncar el fichero");
        free(buffer);
        free(new_buffer);
        close(fd);
        return 1;
    }

    printf("Se insertó 'X' correctamente en el fichero '%s'.\n", filename);

    // Liberar memoria y cerrar el fichero
    free(buffer);
    free(new_buffer);
    close(fd);

    return 0;
}
