// Funktion zum Hinzufügen eines Schlüssel-Wert-Paares
// key: Der Schlüssel als Zeichenkette
// value: Der Wert als Zeichenkette
// Rückgabewert: 0 bei Erfolg, -1 bei einem Fehler
#ifndef KEYVALSTORE_H // Header-Wächter, um doppelte Definitionen zu vermeiden
#define KEYVALSTORE_H

int put(char* key, char* value); // Funktionsdeklaration der Funktion "put"

int del(char* key); // Funktionsdeklaration der Funktion "del"

#endif // Ende des Header-Wächters