#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"



void otvoriDatoteku(FILE** datoteka, const char* naziv, const char* nacin) {
    *datoteka = fopen(naziv, nacin);
    if (*datoteka == NULL) {
        printf("Pogreska pri otvaranju datoteke.\n");
        exit(1);
    }
}

void unesiDijete(const char* const imeDatoteke) {

	FILE* fp = fopen(imeDatoteke, "a+");
	if (fp == NULL) { 
		printf("Datoteka se ne moze otvoriti.\n"); 
	}
    
    DIJETE podatciDjeteta = { 0 };
    int i;
	int unosOk = 0;

    do {
        getchar();
        printf("Unesite OIB djeteta (11 znamenki): ");
        scanf("%s", podatciDjeteta.oib);
        
        int areAllDigits = 1;
        for (i = 0; i < strlen(podatciDjeteta.oib); i++) {
            if (podatciDjeteta.oib[i] < '0' || podatciDjeteta.oib[i] > '9') {
                areAllDigits = 0;
                break;
            }
        }

        if (strlen(podatciDjeteta.oib) == 11 && areAllDigits == 1) {
            unosOk = 1;
        } else {
            printf("Krivi unos! ");
            unosOk = 0;
        }
    } while (unosOk == 0);

    

    getchar();
    printf("Unesite ime djeteta: ");
    scanf("%19[^\n]", podatciDjeteta.ime);

	getchar();
	printf("Unesite prezime djeteta: ");
	scanf("%29[^\n]", podatciDjeteta.prezime);
	


    unosOk = 0;
    do {
	    printf("Unesite broj zivih roditelja djeteta (0, 1 ili 2):");
	    scanf("%d", &podatciDjeteta.brojRoditelja);

	    if (podatciDjeteta.brojRoditelja >=0 && podatciDjeteta.brojRoditelja <=2) {
	        unosOk = 1;
	    }
	    else {
	        printf("Krivi unos! ");
	        unosOk = 0;
	    }
	} while (unosOk == 0);
    

	unosOk = 0; 
	do {
		printf("Unesite broj zaposlenihh roditelja djeteta (0, 1 ili 2): ");
		scanf("%d", &podatciDjeteta.brojZaposlenihRoditelja);

		if (podatciDjeteta.brojZaposlenihRoditelja >= 0 && podatciDjeteta.brojZaposlenihRoditelja <= 2) {
			unosOk = 1;
		}
		else {
			printf("Krivi unos! ");
			unosOk = 0;
		}
	} while (unosOk == 0);

    printf("Unesite broj brace i sestara: ");
    scanf("%d", &podatciDjeteta.brojBraceSestara);

	unosOk = 0;
	do {
		printf("Ima li dijete posebne potrebe? (0-ne, 1-da): ");
		scanf("%d", &podatciDjeteta.dijeteSPosebnimPotrebama);

		if (podatciDjeteta.dijeteSPosebnimPotrebama == 0 || podatciDjeteta.dijeteSPosebnimPotrebama == 1) {
			unosOk = 1;
		}
		else {
			printf("Krivi unos! ");
			unosOk = 0;
		}
	} while (unosOk == 0);
    
	unosOk = 0;
	do {
		printf("Unesite broj godina djeteta (1-6): ");
		scanf("%d", &podatciDjeteta.brojGodina);

		if (podatciDjeteta.brojGodina >= 1 && podatciDjeteta.brojGodina <= 6) {
			unosOk = 1;
		}
		else {
			printf("Krivi unos! ");
			unosOk = 0;
		}
	} while (unosOk == 0);
  
    podatciDjeteta.zbrojBodova = 0;
    podatciDjeteta.zbrojBodova += (2 - podatciDjeteta.brojRoditelja);
    podatciDjeteta.zbrojBodova += podatciDjeteta.brojZaposlenihRoditelja;
    podatciDjeteta.zbrojBodova += podatciDjeteta.brojBraceSestara;
    podatciDjeteta.zbrojBodova += podatciDjeteta.dijeteSPosebnimPotrebama;
    podatciDjeteta.zbrojBodova += podatciDjeteta.brojGodina;

    ispisDjeteta(&podatciDjeteta);


  //  printf("Dijete je uspjesno uneseno u datoteku.\n");
  //  printf("Podatci unesenog djeteta su: %s %s %s zivi roditelji:%d zaposleni roditelji:%d braca i sestre:%d posebne potrebe:%d godine djeteta:%d ukupni bodovi:%d\n",
		//podatciDjeteta.ime, podatciDjeteta.prezime, podatciDjeteta.oib, podatciDjeteta.brojRoditelja, podatciDjeteta.brojZaposlenihRoditelja,
		//podatciDjeteta.brojBraceSestara, podatciDjeteta.dijeteSPosebnimPotrebama, podatciDjeteta.brojGodina, podatciDjeteta.zbrojBodova);
   
	fclose(fp);
}

void ispisDjeteta(DIJETE* podatciDjeteta) {
    printf("Podaci djeteta: ime: %s, prezime: %s, oib: %s, brojRoditelja: %d, brojZaposlenihRoditelja: %d, brojBraceSestara: %d, dijeteSPosebnimPotrebama: %d, brojGodina: %d, zbrojBodova: %d\n",
        podatciDjeteta.ime, podatciDjeteta.prezime, podatciDjeteta.oib, podatciDjeteta.brojRoditelja, podatciDjeteta.brojZaposlenihRoditelja,
        podatciDjeteta.brojBraceSestara, podatciDjeteta.dijeteSPosebnimPotrebama, podatciDjeteta.brojGodina, podatciDjeteta.zbrojBodova);
}

void dodavanjeDjetetaUDatoteku(DIJETE* podatciDjeteta) {
    fprintf(imeDatoteke, "%s %s %s zivi roditelji:%d zaposleni roditelji:%d braca i sestre:%d posebne potrebe:%d godine djeteta:%d ukupni bodovi:%d\n",
        podatciDjeteta.ime, podatciDjeteta.prezime, podatciDjeteta.oib, podatciDjeteta.brojRoditelja, podatciDjeteta.brojZaposlenihRoditelja,
        podatciDjeteta.brojBraceSestara, podatciDjeteta.dijeteSPosebnimPotrebama, podatciDjeteta.brojGodina, podatciDjeteta.zbrojBodova);
}


void pretraziPoPrezimenu(DIJETE* podatciDjeteta, int brojDjece, char* prezime) {
    
    int pronadeno = 0;

    for (int i = 0; i < brojDjece; i++) {
        if (strcmp(podatciDjeteta[i].prezime, prezime) == 0) {
            printf("Podaci za dijete s prezimenom %s:\n", prezime);
            printf("Ime: %s\n", podatciDjeteta[i].ime);
            printf("Prezime: %s\n", podatciDjeteta[i].prezime);
            printf("oib: %s\n", podatciDjeteta[i].oib);
            printf("Broj roditelja: %d\n", podatciDjeteta[i].brojRoditelja);
            printf("Broj zaposlenih roditelja: %d\n", podatciDjeteta[i].brojZaposlenihRoditelja);
            printf("Broj braæe i sestara: %d\n", podatciDjeteta[i].brojBraceSestara);
            printf("Dijete s posebnim potrebama: %d\n", podatciDjeteta[i].dijeteSPosebnimPotrebama);
            printf("Broj godina: %d\n", podatciDjeteta[i].brojGodina);
            printf("Zbroj bodova: %d\n", podatciDjeteta[i].zbrojBodova);
            printf("\n");

            pronadeno = 1;
        }
    }

    if (!pronadeno) {
        printf("Nema podataka za dijete s prezimenom %s.\n", prezime);
    }
}

void pretraziPoOibu(DIJETE* podatciDjeteta, int brojDjece, char* oib) {
    
    int pronadeno = 0;

    for (int i = 0; i < brojDjece; i++) {
        if (strcmp(podatciDjeteta[i].oib, oib) == 0) {
            printf("Podaci za dijete s oib-om %s:\n", oib);
            printf("Ime: %s\n", podatciDjeteta[i].ime);
            printf("Prezime: %s\n", podatciDjeteta[i].prezime);
            printf("oib: %s\n", podatciDjeteta[i].oib);
            printf("Broj roditelja: %d\n", podatciDjeteta[i].brojRoditelja);
            printf("Broj zaposlenih roditelja: %d\n", podatciDjeteta[i].brojZaposlenihRoditelja);
            printf("Broj braæe i sestara: %d\n", podatciDjeteta[i].brojBraceSestara);
            printf("Dijete s posebnim potrebama: %d\n", podatciDjeteta[i].dijeteSPosebnimPotrebama);
            printf("Broj godina: %d\n", podatciDjeteta[i].brojGodina);
            printf("Zbroj bodova: %d\n", podatciDjeteta[i].zbrojBodova);
            printf("\n");

            pronadeno = 1;
        }
    }

    if (!pronadeno) {
        printf("Nema podataka za dijete s oib-om %s.\n", oib);
    }
}

//void sortirajPoPrezimenu(DIJETE* podatciDjeteta, int brojDjece) {
//    int i, j;
//    DIJETE tempPodatci;
//
//    for (i = 0; i < brojDjece - 1; i++) {
//        for (j = i + 1; j < brojDjece; j++) {
//            if (strcmp(podatciDjeteta[i].prezime, podatciDjeteta[j].prezime) > 0) {
//                tempPodatci = podatciDjeteta[i];
//                podatciDjeteta[i] = podatciDjeteta[j];
//                podatciDjeteta[j] = tempPodatci;
//            }
//        }
//    }
//}

void rangLista(DIJETE* podatciDjeteta, int brojDjece) {
    int i, j;
    DIJETE tempPodatci;

    for (i = 0; i < brojDjece - 1; i++) {
        for (j = i + 1; j < brojDjece; j++) {
            if (podatciDjeteta[i].zbrojBodova < podatciDjeteta[j].zbrojBodova) {
                tempPodatci = podatciDjeteta[i];
                podatciDjeteta[i] = podatciDjeteta[j];
                podatciDjeteta[j] = tempPodatci;
            }
        }
    }

    printf("Rang lista:\n");

    for (i = 0; i < brojDjece; i++) {
        printf("%d. mjesto: %s %s (%d bodova)\n", i + 1, podatciDjeteta[i].ime, podatciDjeteta[i].prezime, podatciDjeteta[i].zbrojBodova);
    }

    printf("\n");
}

void ispravakPogresnihPodataka(DIJETE* podatciDjeteta, int brojDjece) {
    char oib[13];
    int pronadeno = 0;

    printf("Unesite oib djeteta cije podatke želite ispraviti: ");
    scanf("%s", oib);

    for (int i = 0; i < brojDjece; i++) {
        if (strcmp(podatciDjeteta[i].oib, oib) == 0) {
            printf("Podaci za dijete s oib-om %s:\n", oib);
            printf("Ime: %s\n", podatciDjeteta[i].ime);
            printf("Prezime: %s\n", podatciDjeteta[i].prezime);
            printf("oib: %s\n", podatciDjeteta[i].oib);
            printf("Broj roditelja: %d\n", podatciDjeteta[i].brojRoditelja);
            printf("Broj zaposlenih roditelja: %d\n", podatciDjeteta[i].brojZaposlenihRoditelja);
            printf("Broj braæe i sestara: %d\n", podatciDjeteta[i].brojBraceSestara);
            printf("Dijete s posebnim potrebama: %d\n", podatciDjeteta[i].dijeteSPosebnimPotrebama);
            printf("Broj godina: %d\n", podatciDjeteta[i].brojGodina);
            printf("Zbroj bodova: %d\n", podatciDjeteta[i].zbrojBodova);
            printf("\n");

           /* printf("Unesite novi broj roditelja (0, 1 ili 2): ");
            scanf("%d", &podatciDjeteta[i].brojRoditelja);
            printf("Unesite novi broj zaposlenih roditelja (0, 1 ili 2): ");
            scanf("%d", &podatciDjeteta[i].brojZaposlenihRoditelja);
            printf("Unesite novi broj brace i sestara: ");
            scanf("%d", &podatciDjeteta[i].brojBraceSestara);
            printf("Unesite dijete s posebnim potrebama (1 - da, 0 - ne): ");
            scanf("%d", &podatciDjeteta[i].dijeteSPosebnimPotrebama);
            printf("Unesite novi broj godina djeteta (1-6): ");
            scanf("%d", &podatciDjeteta[i].brojGodina);*/

            // Ažuriraj zbroj bodova
            podatciDjeteta[i].zbrojBodova = 0;
            podatciDjeteta[i].zbrojBodova += (2 - podatciDjeteta[i].brojRoditelja);
            podatciDjeteta[i].zbrojBodova += podatciDjeteta[i].brojZaposlenihRoditelja;
            podatciDjeteta[i].zbrojBodova += podatciDjeteta[i].brojBraceSestara;
            podatciDjeteta[i].zbrojBodova += podatciDjeteta[i].dijeteSPosebnimPotrebama;
            podatciDjeteta[i].zbrojBodova += podatciDjeteta[i].brojGodina;

            printf("Podaci su uspjesno ispravljeni.\n");

            pronadeno = 1;
        }
    }

    if (!pronadeno) {
        printf("Nema podataka za dijete s oib-om %s.\n", oib);
    }
}

void izbornik(const char* const imeDatoteke) {
    DIJETE* podatciDjeteta = NULL;
    int brojDjece = 0;
    int odabir;

    while (1) {
        printf("Izbornik:\n");
        printf("1. Unos podataka djeteta\n");
        printf("2. Pretrazivanje po prezimenu\n");
        printf("3. Pretrazivanje po oib-u\n");
        printf("4. Sortiranje po prezimenu\n");
        printf("5. Rang lista\n");
        printf("6. Ispravak pogresnih podataka\n");
        printf("7. Oslobadanje memorije i izlaz iz programa\n");
        printf("Odaberite opciju: ");
        scanf("%d", &odabir);

        switch (odabir) {
        case 1:
            unesiDijete(imeDatoteke);
            break;
        case 2:
            if (podatciDjeteta == NULL) {
                printf("Niste unijeli podatke.\n");
            }
            else {
                char prezime[100];
                printf("Unesite prezime za pretraživanje: ");
                scanf("%s", prezime);
                pretraziPoPrezimenu(podatciDjeteta, brojDjece, prezime);
            }
            break;
        case 3:
            if (podatciDjeteta == NULL) {
                printf("Niste unijeli podatke.\n");
            }
            else {
                char oib[12];
                printf("Unesite oib za pretrazivanje: ");
                scanf("%s", oib);
                pretraziPoOibu(podatciDjeteta, brojDjece, oib);
            }
            break;
        case 4:
            if (podatciDjeteta == NULL) {
                printf("Niste unijeli podatke.\n");
            }
            else {
                sortirajPoPrezimenu(podatciDjeteta, brojDjece);
                printf("Podaci su uspjesno sortirani po prezimenu.\n");
            }
            break;
        case 5:
            if (podatciDjeteta == NULL) {
                printf("Niste unijeli podatke.\n");
            }
            else {
                rangLista(podatciDjeteta, brojDjece);
            }
            break;
        case 6:
            if (podatciDjeteta == NULL) {
                printf("Niste unijeli podatke.\n");
            }
            else {
                ispravakPogresnihPodataka(podatciDjeteta, brojDjece);
            }
            break;
        case 7:
            if (podatciDjeteta != NULL) {
                oslobodiMemo(podatciDjeteta);
            }
            printf("Memorija je oslobodena.\n");
            return;
        default:
            printf("Pogresan odabir. Molimo odaberite ponovno.\n");
        }

        printf("\n");
    }
}

 