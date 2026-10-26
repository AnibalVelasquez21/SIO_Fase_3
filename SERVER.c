
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 9000

int main() {
    int servidor_fd, cliente_fd;
    struct sockaddr_in servidor;
    int opcion = 1;

    // Crear socket TCP
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor_fd == -1) {
        perror("Error al crear socket");
        return 1;
    }

    // Permitir reutilizar el puerto
    setsockopt(servidor_fd, SOL_SOCKET,
               SO_REUSEADDR, &opcion, sizeof(opcion));

    // Configura servidor
    memset(&servidor, 0, sizeof(servidor));
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(PUERTO);

    // Asociar socket al puerto 9000
    if (bind(servidor_fd,
             (struct sockaddr *)&servidor,
             sizeof(servidor)) < 0) {
        perror("Error en bind");
        close(servidor_fd);
        return 1;
    }

    // escucha conexiones
    if (listen(servidor_fd, 5) < 0) {
        perror("Error en listen");
        close(servidor_fd);
        return 1;
    }

    printf("Servidor escuchando en puerto %d\n", PUERTO);

    while (1) {
        // espera cliente
        cliente_fd = accept(servidor_fd, NULL, NULL);

        if (cliente_fd < 0) {
            perror("Error en accept");
            continue;
        }

        printf("Cliente conectado correctamente\n");

        // Envia mensaje de bienvenida
        char mensaje[] =
            "Bienvenido al servidor Ubuntu!\n";

        send(cliente_fd, mensaje,
             strlen(mensaje), 0);

        printf("Mensaje enviado al cliente\n");

        // Cierra conexion del cliente
        close(cliente_fd);
    }

    close(servidor_fd);
    return 0;
}
