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
void izbornik(const char* const imeDatoteke);
void otvoriDatoteku(FILE** datoteka, const char* imeDatoteke, const char* nacin);
void unesiDijete(const char* const imeDatoteke, DIJETE* svaDjeca);
void unosPodatakaODjetetu(DIJETE* podatciDjeteta, DIJETE* svaDjeca);
void ispisSveDjece(DIJETE* svaDjeca);
void ispisDjeteta(DIJETE* podatciDjeteta);
DIJETE* ucitavanjeDjeceIzDatoteke(const char* const imeDatoteke, DIJETE* svaDjeca);
DIJETE konvertirajLinijuUStrukturu(char* line);
void izbrisiDijete(const char* const imeDatoteke, DIJETE* svaDjeca, char* oib);
void upisiDijeteUDatoteku(FILE* datoteka, DIJETE* podatciDjeteta);
void pretraziPoPrezimenu(DIJETE* svaDjeca, char* prezime);
void pretraziPoOibu(DIJETE* svaDjeca, char* oib);
void rangLista(DIJETE* podatci, int brojDjece);
void izmjenaPodatakaDjeteta(const char* imeDatoteke, DIJETE* svaDjeca, char* oib);

#endif
