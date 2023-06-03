#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H


typedef struct {

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


DIJETE* zauzmiMemo(int brojDjece);
DIJETE* oslobodiMemo(DIJETE* podatciDjeteta);
void otvoriDatoteku(FILE** datoteka, const char* naziv, const char* nacin);
void unesiDijete(const char* const imeDatoteke);
void pretraziPoPrezimenu(DIJETE* podatci, int brojDjece, char* prezime);
void pretraziPoOibu(DIJETE* podatci, int brojDjece, char* oib);
void sortirajPoPrezimenu(DIJETE* podatci, int brojDjece);
void rangLista(DIJETE* podatci, int brojDjece);
void ispravakPogresnihPodataka(DIJETE* podatci, int brojDjece);
void izbornik(const char* const imeDatoteke);
void ispisDjeteta(DIJETE* podatciDjeteta);


#endif
