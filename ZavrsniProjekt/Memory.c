#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"


DIJETE* zauzimanjeMemPodataka(const int brojDjece) {

    DIJETE* tempZauzimanje = NULL;
    tempZauzimanje = (DIJETE*)calloc(brojDjece, sizeof(DIJETE));

    if (tempZauzimanje == NULL) {
        return NULL;
    }
    return tempZauzimanje;

}

DIJETE* oslobodiMemo(DIJETE* podatciDjeteta) {
    free(podatciDjeteta);

    return NULL;
}