#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP_SERVIDOR "127.0.0.1" // Aqui debes cambiar la IP misaki-kun
#define PUERTO 9000

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int valread;

    // Crear el socket TCP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error al crear el socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);

    // Convertir la dirección IP de texto a binario
    if (inet_pton(AF_INET, IP_SERVIDOR, &serv_addr.sin_addr) <= 0) {
        printf("\nDirección IP inválida / No soportada \n");
        return -1;
    }

    // Conectarse al servidor
    printf("Conectando al servidor %s:%d...\n", IP_SERVIDOR, PUERTO);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error de conexión");
        printf("\nConexión fallida. Asegúrate de que el servidor esté encendido y la IP sea correcta.\n");
        return -1;
    }

    printf("¡Conectado exitosamente al servidor!\n");

    // Leer la respuesta enviada por el servidor
    valread = read(sock, buffer, 1024);
    if (valread > 0) {
        printf("Mensaje recibido del servidor:\n%s", buffer);
    } else {
        printf("No se recibió mensaje del servidor o la conexión se cerró.\n");
    }

    // Cerrar el socket
    close(sock);
    return 0;
}