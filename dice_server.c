
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>  

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE];
    time_t rawtime;  
    struct tm *timeinfo;

 
    srand(time(0));


    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket oluşturulamadı");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bağlama hatası");
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, 3) < 0) {
        perror("Dinleme hatası");
        exit(EXIT_FAILURE);
    }

    printf("Zar Atma Sunucusu başlatıldı. Bağlantı bekleniyor...\n");

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("Kabul hatası");
            exit(EXIT_FAILURE);
        }

       
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        
        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);
        printf("[%s] İstemciden gelen istek: %s\n", timestamp, buffer);

        
        if (strcmp(buffer, "zar at") == 0) {
            int dice_result = (rand() % 6) + 1;  
            sprintf(response, "[%s] Zar sonucu: %d", timestamp, dice_result);
        } else {
            sprintf(response, "[%s] Geçersiz istek! 'zar at' komutu gönderin.", timestamp);
        }

        
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
