#include <string.h> //um strcpy() zu verwenden

#define MaxKeyLength 10
#define MaxValueLength 10
#define MaxKeyValuePairLength 2


typedef struct{
    char key[MaxKeyLength];
    char value[MaxValueLength];
}kvPair;

kvPair kvp1[MaxKeyValuePairLength];

//nur zum testen, nachher wirklich leer lassen!
void SETkvsDEFAULT(){
    for (int i = 0; i < (MaxKeyValuePairLength); ++i) {
        strcpy(kvp1[i].key,"-EMPTY-");
        strcpy(kvp1[i].value,"-EMPTY-");
    }
}

void SHOW(){
    for (int i = 0; i < MaxKeyValuePairLength; ++i) {
        printf("current Key (K%d):\t %s\n",i+1,kvp1[i].key);
        printf("current Value (VtoK%d):\t %s\n\n",i+1,kvp1[i].value);
    }
}


/* put() soll einen Wert (value) mit dem Schlüsselwort (key) hinterlegen.
 * Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden.
 * Der Rückgabewert der Funktion könnte Auskunft dazu geben.
*/
int PUT (char * key, char * value);


/*
 * get() soll einen Schlüsselwert (key) in der Datenhaltung suchen und den hinterlegten Wert (value) zurückgeben.
 * Ist der Wert nicht vorhanden, wird durch einen Rückgabewert <0 darauf aufmerksam gemacht.
*/
int GET (char * key, char * res);

/*
 * del() soll einen Schlüsselwert suchen und zusammen mit dem Wert aus der Datenhaltung entfernen.
 * */
int DEL (char * key);