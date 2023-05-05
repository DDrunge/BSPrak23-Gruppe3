#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyValStore.h"

#define MAX_KEY_LENGTH 50
#define MAX_VALUE_LENGTH 200
#define MAX_KVPAIRS 100

// Definition eines Structs für eine Key-Value Paar
typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValuePair;

// Array zum Halten der Key-Value Paare
KeyValuePair kvPairs[MAX_KVPAIRS];

// Anzahl der aktuellen Key-Value Paare im Array
int numKVPairs = 0;

// Funktion zum Einfügen eines neuen Key-Value Paares oder Aktualisieren des Wertes, falls der Key bereits existiert
int put(char* key, char* value) {
// Überprüfung, ob der Key bereits im Array vorhanden ist
    for (int i = 0; i < numKVPairs; i++) {
        if (strcmp(key, kvPairs[i].key) == 0) {
// Key bereits vorhanden, update den Wert
            strcpy(kvPairs[i].value, value);
            return 0;
        }
    }
    // Key ist nicht vorhanden, füge das neue Key-Value Paar zum Array hinzu
    if (numKVPairs >= MAX_KVPAIRS) {
        // Key-Value Store ist voll, gib einen Fehlercode zurück
        return -1;
    }
    strcpy(kvPairs[numKVPairs].key, key);
    strcpy(kvPairs[numKVPairs].value, value);
    numKVPairs++;

    return 0;
}

// Funktion zum Abrufen des Werts eines bestimmten Keys
int get(char* key, char* res) {
// Suche nach dem Key im Array
    for (int i = 0; i < numKVPairs; i++) {
        if (strcmp(key, kvPairs[i].key) == 0) {
// Key gefunden, kopiere den Wert ins res-Buffer und gib den Erfolgscode zurück
            strcpy(res, kvPairs[i].value);
            return 0;
        }
    }
    // Key nicht gefunden, gib einen Fehlercode zurück
    return -1;
}

// Funktion zum Löschen eines bestimmten Keys
int del(char* key) {
// Suche nach dem Key im Array
    for (int i = 0; i < numKVPairs; i++) {
        if (strcmp(key, kvPairs[i].key) == 0) {
// Key gefunden, entferne das Key-Value Paar aus dem Array
            for (int j = i; j < numKVPairs - 1; j++) {
                kvPairs[j] = kvPairs[j + 1];
            }
            numKVPairs--;
            return 0;
        }
    }
    // Key nicht gefunden, gib einen Fehlercode zurück
    return -1;
}