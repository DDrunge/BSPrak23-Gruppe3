#include "sub.h" // Einbinden der Header-Datei sub.h
#include "KeyValStore.h" // Einbinden der Header-Datei KeyValStore.h
void strip_newline(char* str) { // Definition der Funktion strip_newline mit Übergabeparameter char-Pointer str
    char* pos = strchr(str, '\n'); // Initialisierung eines char-Pointers pos mit dem Rückgabewert von strchr(), welches die Position des ersten Vorkommens von '\n' in str zurückgibt oder NULL, wenn '\n' nicht gefunden wurde
    if (pos != NULL) { // Wenn pos ungleich NULL ist, d.h. '\n' in str gefunden wurde
        *pos = '\0'; // Setze den Wert an pos auf '0', um das Zeilenende zu entfernen
    }
}