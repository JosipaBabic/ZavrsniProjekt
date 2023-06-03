#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"


DIJETE* zauzmiMemoriju(const int brojDjece) {

    DIJETE* tempZauzimanje = NULL;
    tempZauzimanje = (DIJETE*)calloc(brojDjece, sizeof(DIJETE));

    if (tempZauzimanje == NULL) {
        perror("Zauzimanje memorije za djecu");
        exit(EXIT_FAILURE);
    }
    return tempZauzimanje;

}

void oslobodiMemoriju(DIJETE* svaDjeca) {
    if (svaDjeca != NULL) {
        free(svaDjeca);
        svaDjeca = NULL;
    }
}