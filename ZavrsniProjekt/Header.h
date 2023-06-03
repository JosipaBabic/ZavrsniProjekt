#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H


typedef struct {
    long id;

    char oib[13];
    char ime[20];
    char prezime[30];

    int brojRoditelja;
    int brojZaposlenihRoditelja;
    int brojBraceSestara;
    int dijeteSPosebnimPotrebama;
    int brojGodina;
    int zbrojBodova;

} DIJETE;


DIJETE* zauzmiMemoriju(const int brojDjece);
void oslobodiMemoriju(DIJETE* svaDjeca);
void otvoriDatoteku(FILE** datoteka, const char* imeDatoteke, const char* nacin);
void unesiDijete(const char* const imeDatoteke, DIJETE* svaDjeca);
void pretraziPoPrezimenu(DIJETE* svaDjeca, char* prezime);
void pretraziPoOibu(DIJETE* svaDjeca, char* oib);
void rangLista(DIJETE* podatci, int brojDjece);
void ispravakPogresnihPodataka(DIJETE* podatci, int brojDjece);
void izbornik(const char* const imeDatoteke);
void ispisDjeteta(DIJETE* podatciDjeteta);
DIJETE konvertirajLinijuUStrukturu(char* line);
DIJETE* ucitavanjeDjeceIzDatoteke(const char* const imeDatoteke, DIJETE* svaDjeca);
void dodajDijeteUDatoteku(const char* const imeDatoteke, DIJETE* podatciDjeteta);
void upisiDijeteUDatoteku(FILE* datoteka, DIJETE* podatciDjeteta);
int izbrisiDijete(const char* const imeDatoteke, DIJETE* svaDjeca, char* oib);

#endif
