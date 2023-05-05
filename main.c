#include <stdio.h>       // Standard-Input/Output Header-Datei
#include <stdlib.h>      // Standard-Header-Datei
#include <string.h>      // String-Header-Datei
#include <sys/socket.h>  // Socket-Header-Datei
#include <arpa/inet.h>   // Header-Datei für Internet-Adressen
#include <unistd.h>      // Header-Datei für POSIX-API
#include "main.h"        // Header-Datei für die Funktionen von main.c

#define PORT 5678        // Der Port, auf dem der Server hört
#define MAX_CLIENTS 1    // Maximale Anzahl von Clients, die gleichzeitig bedient werden können

void process_client(int client_socket);    // Funktion zur Verarbeitung von Client-Anfragen
void send_result(int client_socket, char* result);    // Funktion zur Übertragung von Ergebnissen an Clients
int get(char* key, char* res);    // Funktion zum Lesen von Schlüssel-Wert-Paaren aus dem Speicher
int put(char* key, char* value);    // Funktion zum Schreiben von Schlüssel-Wert-Paaren in den Speicher
int del(char* key);    // Funktion zum Löschen von Schlüssel-Wert-Paaren aus dem Speicher

int main(int argc, char* argv[]) {
    int server_socket, client_socket, c;    // Socket-Deskriptoren und Verbindungsparameter
    struct sockaddr_in server, client;    // Strukturen für Server- und Client-Adressen

    // Socket für den Server erstellen
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // sockaddr_in-Struktur für den Server vorbereiten
    server.sin_family = AF_INET;    // Adressfamilie: IPv4
    server.sin_addr.s_addr = INADDR_ANY;    // Verbinden auf allen verfügbaren IP-Adressen
    server.sin_port = htons(PORT);    // Port-Nummer in Netzwerk-Byte-Reihenfolge umwandeln

    // Socket an die Adresse binden
    if (bind(server_socket, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("Failed to bind socket to address");
        exit(EXIT_FAILURE);
    }

    // Auf eingehende Verbindungen warten
    listen(server_socket, MAX_CLIENTS);

    // Eingehende Verbindungen akzeptieren
    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(server_socket, (struct sockaddr*) &client, (socklen_t*) &c))) {
        process_client(client_socket);
    }

    if (client_socket < 0) {
        perror("Failed to accept connection");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void process_client(int client_socket) {
    char buffer[1024] = {0};    // Puffer zum Empfangen von Client-Anfragen
    char command[5] = {0};    // Speichert den Befehl, der von der Client-Anfrage übergeben wird
    char key[100] = {0};    // Speichert den Schlüssel, auf den der Befehl angewendet wird
    char value[100] = {
            0}; // Ein char-Array mit 100 Stellen, das mit Nullen initialisiert ist, um den vom Befehl gelesenen Wert oder den eingegebenen Wert zu speichern.
    char result[100] = {
            0}; // Ein char-Array mit 100 Stellen, das mit Nullen initialisiert ist, um das Ergebnis des Befehls zu speichern.

// Unendliche Schleife
    while (1) {
// Empfangen eines Befehls vom Client
        read(client_socket, buffer, 1024);
// Parsen des Befehls in separate Strings
        sscanf(buffer, "%s %s %s", command, key, value);

        // Befehlsverarbeitung
        if (strcmp(command, "GET") == 0) { // Wenn der Befehl "GET" lautet
            int res = get(key,
                          result); // Abrufen des Werts für den Schlüssel "key" und Speichern des Ergebnisses in "result"
            if (res < 0) { // Wenn das Ergebnis kleiner als Null ist, d.h. der Schlüssel nicht existiert
                sprintf(result, "GET:%s:key_nonexistent",
                        key); // Setzen des Ergebnisses auf eine Fehlermeldung mit dem Schlüssel, der nicht existiert
            } else { // Wenn der Schlüssel existiert
                sprintf(result, "GET:%s:%s", key, result); // Setzen des Ergebnisses auf den Schlüssel und seinen Wert
            }
            send_result(client_socket, result); // Senden des Ergebnisses an den Client
        } else if (strcmp(command, "PUT") == 0) { // Wenn der Befehl "PUT" lautet
            int res = put(key, value); // Speichern des Werts "value" für den Schlüssel "key"
            sprintf(result, "PUT:%s:%s", key,
                    value); // Setzen des Ergebnisses auf den Schlüssel und den gespeicherten Wert
            send_result(client_socket, result); // Senden des Ergebnisses an den Client
        } else if (strcmp(command, "DEL") == 0) { // Wenn der Befehl "DEL" lautet
            int res = del(key); // Löschen des Schlüssels "key"
            if (res < 0) { // Wenn das Ergebnis kleiner als Null ist, d.h. der Schlüssel nicht existiert
                sprintf(result, "DEL:%s:key_nonexistent",
                        key); // Setzen des Ergebnisses auf eine Fehlermeldung mit dem Schlüssel, der nicht existiert
            } else { // Wenn der Schlüssel existiert
                sprintf(result, "DEL:%s:key_deleted",
                        key); // Setzen des Ergebnisses auf eine Erfolgsmeldung mit dem gelöschten Schlüssel
            }
            send_result(client_socket, result); // Senden des Ergebnisses an den Client
        } else if (strcmp(command, "QUIT") == 0) { // Wenn der Befehl "QUIT" lautet
            close(client_socket); // Schließen des Sockets
            break; // Beenden der Schleife
        }
    }
}



// Funktion zum Senden des Ergebnisses an den Client
        void send_result(int client_socket, char *result) {
            write(client_socket, result, strlen(result));
        }

