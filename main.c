/*copy-paste from lecture source code (echo-server_adr):*/
#include <stdio.h> //standard in- / output
#include <stdlib.h> //Umwandlung von Zahlen für Speicherverwaltung u.ä.
#include <unistd.h> //provides access to POSIX operating system API
#include <sys/types.h> //collection of typedef symbols and structures
#include <sys/socket.h> //makes socklen_t available
#include <netinet/in.h> //definitions for the internet protocol family

#include "keyValStore.c"
#include "sub.c"

#define BUFFSIZE 1024 //Anzahl der Bytes, die der Client sendet?
#define PORT 5672 //(lt. Aufgabenstellung 5678)
#define BACKLOG 5 // Länge der Warteschlange der Clients die eine Verbindung aufbauen wollen
#define ENDLOSSCHLEIFE 1

int main () {
    int server_socket_fd;      //Filedescriptor (Identifikation des Sockets)
    int connection_fd;  //Verbindungsdescriptor (eigentliche Kommunikation / Senden und Empfangen)

    struct sockaddr_in server_adr, client_adr; //zum binden der Adresse, struct für die Adresse
    socklen_t client_len = sizeof(client_adr); //client_addr_size; -> Länge der Client Daten
    int bytes_read;
    char in[BUFFSIZE];
    //client_len= sizeof(client_adr);


/* -socket()- [socket erstellen]*/
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    /*
        // AF_INET              // domain
        // Protokoll-Familie die benutzt werden soll (hier: IPv4)
        // IPv4 stands for Internet Protocol version 4.
        // It is the underlying technology that makes it possible for us to connect our devices to the web.
        // Whenever a device accesses the Internet, it is assigned a unique, numerical IP address.
        // für "internetbasierte Kommunikation"
        // SOCK_STREAM          // type
        // Typ der Kommunikation des Sockets
        // Alternativen:
        // SOCK_DGRAM   -> UDP - datagrambasierte Kommunikation
        // SOCK_STREAM  -> TCP - verbindungsorientierte Kommunikation
        // 0                    // protocol
        // Parameter, um das Protokoll genauer zu spezifizieren, falls als Typ SOCK_RAW genutzt wird
        // (SOCK_STREAM ist automatisch TCP, SOCK_DGRAM ist UDP, Parameter i.d.R. 0)
    */

    if (server_socket_fd < 0) {
        perror("socket build failed! abort mission! ABORT MISSION!!");
        exit(-1); // server_socket_fd gibt 0 zurück, wenn efolgreich!
    }
    // zum testen:
    puts("~~~~ Socket successfully created! yaay!\n");


/* -bind()- [socket an Adresse binden]*/

    /*Socket Optionen setzen für schnelles wiederholtes Binden der Adresse*/
    /*Code aus EchoServer übernommen*/
    int option = 1;
    setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));

    /*binden der Adresse:*/
    //oben bereits initialisiert: "struct sockaddr_in server_adr"
    server_adr.sin_family = AF_INET;
    server_adr.sin_addr.s_addr = INADDR_ANY;
    server_adr.sin_port = htons(PORT);
    /*
        //server_adr.sin_family=AF_INET;
        // domain, siehe Notiz oben in socket
        //server_adr.sin_addr.s_addr=INADDR_ANY;
        // Verwendung wie Konstante um gleichzeitig auf alle IP-Adressen zu binden
        // sonst: localhost oder 10.3.88.178
        //server_adr.sin_port= htons(PORT);
        // PORT aktuell (lt. Aufgabenstellung) 5678, im EchoServer 4711
    */

    int result = bind(server_socket_fd, (struct sockaddr *) &server_adr, sizeof(server_adr));
    /*
        // server_socket_fd
        // Filedescriptor des Sockets, der an die Adresse gebunden werden soll
        // (struct sockaddr*) &server_adr
        // address
        // Adresse im Netzwerk, an die das Socket gebunden werden soll
        // besteht aus IP-Adresse und Port, Typ ist Pointer auf "struct sockaddr"
        // sizeof(server_adr)
        // "address"_len
        // Größe des Structs, des zweiten Parameters (Anzahl der Bytes im Speicher)
    */
    if (result < 0) {
        perror("bind() didn´t work...is there a socket on this port already?");
        exit(-1);
    }

    // zum testen:
    puts("~~~~ Socket successfully bound! yaay!\n");


/* -listen()- [socket auf Verbindung hören lassen]*/

    int ret = listen(server_socket_fd, BACKLOG);
    /*
        //int ret;
        // Rückgabewert 0 wenn alles geklappt hat
        //BACKLOG; (int)
        // über #define oben bereits initialisiert; Länge der Warteschlange für Clients
        // server_socket_fd;
        //-> Filedescriptor
    */
    if (ret < 0) {
        perror("the socket didn´t hear anything...what happened here?");
        exit(-1); // server_socket_fd gibt 0 zurück, wenn efolgreich!
    }

    // zum testen:
    puts("~~~~ Socket-Server is listening, please follow the instructions:\n");

//bis hier: ein Programm das auf eingehende Verbindungen hören kann!

    connection_fd = accept(server_socket_fd, (struct sockaddr *) &client_adr, &client_len);
    puts("test-2");






//SETkvsDEFAULT();
//SHOW();

/*aus sub.c: (nur printf) - Instructions für das Nutzen des KeyValStore:*/
//TextFKVS();



// -accept(), read(), write()-



    /*
    while (ENDLOSSCHLEIFE) {

        //wie printf, hat aber anders nicht funktioniert
        puts("test-1");

        // -accept()- [Verbindung akzeptieren]

        connection_fd = accept(server_socket_fd, (struct sockaddr *) &client_adr, &client_len);


            // connection_fd
            // oben bereits initialisiert
            // Verbindungsdescriptor (eigentliche Kommunikation / Senden und Empfangen)
            // accept ()
            // blockierender Aufruf!
            // beim Aufruf wartet das Programm (verschwindet im accept call), und kehrt dann zurück, wenn sich ein Client verbunden hat
            // server_socket_fd
            // dient hier nur zum Aufbau der Verbindung, es finden noch keine Kommunikation statt!
            // client_adr
            // Pointer auf Struktur, in dem Informationen zum Client geschrieben werden
            // z. B. Client IP-Adresse, Pointer auf Struktur vom Typ "sockaddr"
            // client_len
            // länge der Struktur die für den client_adr übergeben wird


        close(connection_fd);
        puts("test-2");

        if (connection_fd < 0) {
            perror("Connection not accepted! I repeat; CONNECTION NOT ACCEPTED!");
            exit(-1);
        }

        puts("test-3");

        // zum testen:
        //printf("~~~~ Connection accepted, nice!\n");


         -read()- [lesen der Daten die der Client schickt]

        bytes_read = read(connection_fd, in, BUFFSIZE);

        puts("test-4");

        // zum testen:
        //printf("~~~~ Server is reading, please wait..\n");

         -write()- [ausgeben der Daten, solange der Client was schickt]

        while (bytes_read > 0) {
            printf("server working, please wait a moment..");

            write(connection_fd, in, bytes_read);
            bytes_read = read(connection_fd, in, BUFFSIZE);
        }
        close(connection_fd);
    }*/

    close(server_socket_fd);
}





/*Für später:*/

// (domain): client_adr.sin_family = AF_INET;
// client_adr.sin_addr.s_addr = INADDR_ANY; //Client IP-Adresse hinzufügen?
// Verwendung wie Konstante um gleichzeitig auf alle IP-Adressen zu binden
// sonst: localhost oder 10.3.88.178
// client_adr.sin_port = htons(5678);
// host byte order to network byte order (?)

/* -recv()/send()- [Daten senden und empfangen]*/
// read()/write()   -> für generelle I/O
// recv()/send()    -> für netzwerkbasierte I/O

/*
 * number_bytes = recv(connection_fd, buffer, number_bytes, flags);
 * number_bytes = send(connection_fd, buffer, number_bytes, flags);
 *
 *  // number_bytes
 *      // Anzahl der Bytes, die gesendet bzw. empfangen werden
 *      // Kann 0 sein
 *      // Negativ wenn Fehler
 *  // connection_fd
 *      // Verbindungsdescriptor, über den empfangen bzw. gesendet werden soll
 *  // buffer
 *      // Buffer, der gesendet bzw. in  dem etwas empfangen werden soll.
 *  // flags
 *      // bspw. zur Vorschau von Daten auf dem Stream oder Warten auf Vollständigkeit
 */
/* -select()- */
// (Bei mehreren Filedescriptoren)
