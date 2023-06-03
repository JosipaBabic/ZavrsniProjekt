#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include "Header.h"


static int brojDjece = 0;

void otvoriDatoteku(FILE** datoteka, const char* imeDatoteke, const char* nacin) {
    *datoteka = fopen(imeDatoteke, nacin);
    if (*datoteka == NULL) {
        printf("Pogreska pri otvaranju datoteke.\n");
        exit(EXIT_FAILURE);
    }
}

void unesiDijete(const char* const imeDatoteke, DIJETE* svaDjeca) {
    
    DIJETE podatciDjeteta = { 0 };
    int i;
	int unosOk = 0, sveSuZnamenke = 1, oibUnesen = 0;

    podatciDjeteta.id = time(NULL);

    do {
        getchar();
        printf("Unesite OIB djeteta (11 znamenki): ");
        scanf("%s", podatciDjeteta.oib);
        
        sveSuZnamenke = 1;
        for (i = 0; i < strlen(podatciDjeteta.oib); i++) {
            if (podatciDjeteta.oib[i] < '0' || podatciDjeteta.oib[i] > '9') {
                sveSuZnamenke = 0;
                break;
            }
        }

        oibUnesen = 0;
        for (i = 0; i < brojDjece; i++) {
            if (strcmp(svaDjeca[i].oib, podatciDjeteta.oib) == 0) {
                oibUnesen = 1;
                break;
            }
        }

        if (strlen(podatciDjeteta.oib) == 11 && sveSuZnamenke == 1 && oibUnesen == 0) {
            unosOk = 1;
        } else {
            unosOk = 0;
            if (oibUnesen == 1) {
                printf("Dijete s tim OIB-om je vec uneseno! ");
            }
            else {
                printf("Krivi format unosa! ");
            }
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
		printf("Unesite broj zaposlenih roditelja djeteta (0 - %d): ", podatciDjeteta.brojRoditelja);
		scanf("%d", &podatciDjeteta.brojZaposlenihRoditelja);

		if (podatciDjeteta.brojZaposlenihRoditelja >= 0 && podatciDjeteta.brojZaposlenihRoditelja <= podatciDjeteta.brojRoditelja) {
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

    dodajDijeteUDatoteku(imeDatoteke, &podatciDjeteta);

    printf("\nDodani su podatci za dijete:\n");
    ispisDjeteta(&podatciDjeteta);
}

void ispisSveDjece(DIJETE* svaDjeca) {
    int i;

    printf("\nSVA DJECA:\n");
    for (i = 0; i < brojDjece; i++) {
        ispisDjeteta(svaDjeca + i);
    }
}

void ispisDjeteta(DIJETE* podatciDjeteta) {
    printf("\nPodatci djeteta:\nId: %ld, OIB: %s, Ime: %s, Prezime: %s, BrojRoditelja: %d, BrojZaposlenihRoditelja: %d, BrojBraceSestara: %d, DijeteSPosebnimPotrebama: %d, BrojGodina: %d, ZbrojBodova: %d\n",
        podatciDjeteta->id, podatciDjeteta->oib, podatciDjeteta->ime, podatciDjeteta->prezime, podatciDjeteta->brojRoditelja, podatciDjeteta->brojZaposlenihRoditelja,
        podatciDjeteta->brojBraceSestara, podatciDjeteta->dijeteSPosebnimPotrebama, podatciDjeteta->brojGodina, podatciDjeteta->zbrojBodova);
}

DIJETE* ucitavanjeDjeceIzDatoteke(const char* const imeDatoteke, DIJETE* svaDjeca) {
    char znak;
    char linija[100];
    FILE* datoteka;
    DIJETE* svaDjecaNovo;

    oslobodiMemoriju(svaDjeca);

    otvoriDatoteku(&datoteka, imeDatoteke, "r");

    brojDjece = 0;
    for (znak = getc(datoteka); znak != EOF; znak = getc(datoteka))
        if (znak == '\n') // Increment count if this character is newline
            brojDjece = brojDjece + 1;
    printf("\nBroj djece u datoteci: %d\n", brojDjece);

    svaDjecaNovo = zauzmiMemoriju(brojDjece);

    rewind(datoteka);
    int i = 0;
    while (fgets(linija, 100, datoteka)) {
        *(svaDjecaNovo + i) = konvertirajLinijuUStrukturu(linija);
        i++;
    }
    fclose(datoteka);

    //ispisSveDjece(svaDjeca);

    return svaDjecaNovo;
}

DIJETE konvertirajLinijuUStrukturu(char* linija) {
     
    char* dijeloviLinije[11];
    int i = 1;

    char* token = strtok(linija, ",");
    dijeloviLinije[0] = token;
    while (token != NULL) {
        token = strtok(NULL, ",");
        dijeloviLinije[i] = token;
        i++;
    }
 
    DIJETE* podatciDjeteta;
    podatciDjeteta = malloc(sizeof(DIJETE));
    if (podatciDjeteta == NULL) {
        printf("Ran out of memory\n");
        exit(EXIT_FAILURE);
    }
    sscanf(dijeloviLinije[0], "%ld", &podatciDjeteta->id);
    sscanf(strdup(dijeloviLinije[1]), "%s", podatciDjeteta->oib);
    sscanf(strdup(dijeloviLinije[2]), "%s", podatciDjeteta->ime);
    sscanf(strdup(dijeloviLinije[3]), "%s", podatciDjeteta->prezime);
    sscanf(dijeloviLinije[4], "%d", &podatciDjeteta->brojRoditelja);
    sscanf(dijeloviLinije[5], "%d", &podatciDjeteta->brojZaposlenihRoditelja);
    sscanf(dijeloviLinije[6], "%d", &podatciDjeteta->brojBraceSestara);
    sscanf(dijeloviLinije[7], "%d", &podatciDjeteta->brojGodina);
    sscanf(dijeloviLinije[8], "%d", &podatciDjeteta->dijeteSPosebnimPotrebama);
    sscanf(dijeloviLinije[9], "%d", &podatciDjeteta->zbrojBodova);

    return *podatciDjeteta;
}

int izbrisiDijete(const char* const imeDatoteke, DIJETE* svaDjeca, char* oib) {
    int i, obrisano = 0;
    FILE* datoteka;

    otvoriDatoteku(&datoteka, imeDatoteke, "w");
    for (i = 0; i < brojDjece; i++) {
        if (strcmp(svaDjeca[i].oib, oib) != 0) {
            upisiDijeteUDatoteku(datoteka, svaDjeca + i);
        }
        else {
            obrisano++;
        }
    }
    fclose(datoteka);

    if (obrisano) {
        printf("\nIzbrisani su podatci za dijete s OIB-om %s.\n", oib);
    }
    else {
        printf("\nNema podataka za dijete s OIB-om %s.\n", oib);
    }

    return obrisano;
}

void dodajDijeteUDatoteku(const char* const imeDatoteke, DIJETE* podatciDjeteta) {
    FILE* datoteka;
    otvoriDatoteku(&datoteka, imeDatoteke, "a+");
    upisiDijeteUDatoteku(datoteka, podatciDjeteta);
    fclose(datoteka);
}

void upisiDijeteUDatoteku(FILE* datoteka, DIJETE* podatciDjeteta) {
    fprintf(datoteka, "%ld,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
        podatciDjeteta->id,
        podatciDjeteta->oib,
        podatciDjeteta->ime,
        podatciDjeteta->prezime,
        podatciDjeteta->brojRoditelja,
        podatciDjeteta->brojZaposlenihRoditelja,
        podatciDjeteta->brojBraceSestara,
        podatciDjeteta->dijeteSPosebnimPotrebama,
        podatciDjeteta->brojGodina,
        podatciDjeteta->zbrojBodova);
}

void pretraziPoPrezimenu(DIJETE* svaDjeca, char* prezime) {
    
    int i, pronadeno = 0;

    printf("\nIspis djece s prezimenom %s:\n", prezime);
    for (i = 0; i < brojDjece; i++) {
        if (strcmp(svaDjeca[i].prezime, prezime) == 0) {
            ispisDjeteta(svaDjeca + i);
            pronadeno = 1;
        }
    }

    if (!pronadeno) {
        printf("Nema podataka za dijete s prezimenom %s.\n", prezime);
    }
}

void pretraziPoOibu(DIJETE* svaDjeca, char* oib) {
    
    int i, pronadeno = 0;

    printf("\nIspis djece s OIB-om %s:\n", oib);
    for (i = 0; i < brojDjece; i++) {
        if (strcmp(svaDjeca[i].oib, oib) == 0) {
            ispisDjeteta(svaDjeca + i);
            pronadeno = 1;
        }
    }

    if (!pronadeno) {
        printf("Nema podataka za dijete s OIB-om %s.\n", oib);
    }
}

void rangLista(DIJETE* svaDjeca, int brojDjece) {
    int i, j;
    DIJETE tempPodatci;

    for (i = 0; i < brojDjece - 1; i++) {
        for (j = i + 1; j < brojDjece; j++) {
            if (svaDjeca[i].zbrojBodova < svaDjeca[j].zbrojBodova) {
                tempPodatci = svaDjeca[i];
                svaDjeca[i] = svaDjeca[j];
                svaDjeca[j] = tempPodatci;
            }
        }
    }

    printf("Rang lista:\n");

    for (i = 0; i < brojDjece; i++) {
        printf("%d. mjesto: %s %s (%d bodova)\n", i + 1, svaDjeca[i].ime, svaDjeca[i].prezime, svaDjeca[i].zbrojBodova);
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
    
    static DIJETE* svaDjeca = NULL;
    int odabir;
    char oib[12], prezime[30];

    svaDjeca = ucitavanjeDjeceIzDatoteke(imeDatoteke, svaDjeca);

    while (1) {
        printf("\n-------------------\n");
        printf("Izbornik:\n");
        printf("1. Unos podataka djeteta\n");
        printf("2. Izmjena podataka djeteta\n");
        printf("3. Brisanje podataka djeteta\n");
        printf("4. Rang lista\n");
        printf("5. Pretrazivanje po prezimenu\n");
        printf("6. Pretrazivanje po OIB-u\n");
        printf("7. Oslobadanje memorije i izlaz iz programa\n");
        printf("Odaberite opciju: ");
        scanf("%d", &odabir);

        switch (odabir) {
        case 1:
            unesiDijete(imeDatoteke, svaDjeca);
            svaDjeca = ucitavanjeDjeceIzDatoteke(imeDatoteke, svaDjeca);
            break;
        case 2: 
            ispravakPogresnihPodataka(svaDjeca, brojDjece);
            break;
        case 3:
            printf("Unesite OIB za brisanje: ");
            scanf("%s", oib);
            if (izbrisiDijete(imeDatoteke, svaDjeca, oib)) {
                svaDjeca = ucitavanjeDjeceIzDatoteke(imeDatoteke, svaDjeca);
            }
            break;
        case 4: 
            rangLista(svaDjeca, brojDjece);
            break;
        case 5:
            printf("Unesite prezime za pretrazivanje: ");
            scanf("%s", prezime);
            pretraziPoPrezimenu(svaDjeca, prezime);
            break;
        case 6:
            printf("Unesite OIB za pretrazivanje: ");
            scanf("%s", oib);
            pretraziPoOibu(svaDjeca, oib);
            break;
        case 7:
            oslobodiMemoriju(svaDjeca);
            printf("Memorija je oslobodena.\n");
            return;
        default:
            printf("Pogresan odabir. Molimo odaberite ponovno.\n");
        }

        printf("\n");
    }
}

 