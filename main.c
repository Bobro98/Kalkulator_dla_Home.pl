#include <stdio.h>
#include <stdlib.h>
#include "string.h"

char** wczytaj_dzialanie(char ** dzialania, int* liczba_dzialan)
{
    char wejscie[100];

    /* przyk³ad
    3
    4 + 2 - 1
    1 + 4 / 3 * 2
    1 + 3 + 5 + 5
    */
    printf("Podaj liczb\251 dzia\210a\344 do wykonania oraz r\242wnania ");

    scanf("%d", liczba_dzialan);

    dzialania=(char**)malloc(*liczba_dzialan*sizeof(char*));

    int i;
    for(i = 0; i <= *liczba_dzialan; i++)
    {
        fgets(wejscie, sizeof wejscie, stdin);

        char str[] = "\n";
        int koniec_linii = strcspn(wejscie, str);
        dzialania[i] = (char*)malloc(sizeof(char) * koniec_linii + 1);
        strcpy(dzialania[i], wejscie);
        //printf("%s", dzialanie[i]);
    }
    return dzialania;
}

char* usun_spacje(char* s) {
     int p = -1, q = 0;

     while (s[++p] != '\0')
        if (s[p] != ' ')
            s[q++] = s[p];
     s[q] = '\0';
     return s;
}

double* odczytaj_liczby(char* s, int *ilosc_odczytanych_liczb)
{

    double* liczby;

    int licznik = 1;
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '+')
            licznik++;
        if(s[i] == '-')
            licznik++;
        if(s[i] == '/')
            licznik++;
        if(s[i] == '*')
            licznik++;
        i++;
    }
    liczby = (double*)malloc(licznik * sizeof(double));
    *ilosc_odczytanych_liczb = licznik;

    int k = 0;
    int poczatek = 0;
    int koniec = 0;
    char* liczba = NULL;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '+')
        {
            koniec = i;
            liczba = (char*)malloc((koniec - poczatek) * sizeof(char) + 1);
            memcpy( liczba, &s[poczatek], (koniec - poczatek));
            liczba[(koniec - poczatek) + 1] = '\0';
            liczby[k] = atof(liczba);
            k++;
            poczatek = koniec + 1;
        }
        if(s[i] == '-')
            {
                koniec = i;
                liczba = (char*)malloc((koniec - poczatek) * sizeof(char) + 1);
                memcpy( liczba, &s[poczatek], (koniec - poczatek));
                liczba[(koniec - poczatek) + 1] = '\0';
                liczby[k] = atof(liczba);
                k++;
                poczatek = koniec + 1;
            }
        if(s[i] == '/')
            {
                koniec = i;
                liczba = (char*)malloc((koniec - poczatek) * sizeof(char) + 1);
                memcpy( liczba, &s[poczatek], (koniec - poczatek));
                liczba[(koniec - poczatek) + 1] = '\0';
                liczby[k] = atof(liczba);
                k++;
                poczatek = koniec + 1;
            }
        if(s[i] == '*')
            {
                koniec = i;
                liczba = (char*)malloc((koniec - poczatek) * sizeof(char) + 1);
                memcpy( liczba, &s[poczatek], (koniec - poczatek));
                liczba[(koniec - poczatek) + 1] = '\0';
                liczby[k] = atof(liczba);
                k++;
                poczatek = koniec + 1;
            }
        i++;
    }
    liczba = (char*)malloc((strlen(s) - poczatek) * sizeof(char) + 1);
    memcpy( liczba, &s[poczatek], (strlen(s) - poczatek));
    liczba[(strlen(s) - poczatek) + 1] = '\0';
    liczby[k] = atof(liczba);
    free(liczba);
    //printf("%d %d %d %d %d \n",liczby[0],liczby[1],liczby[2],liczby[3], liczby[4]);

    //char str[] = "/*+-";
    return liczby;
}

double wykonaj_rownanie(char* s)
{
    int ilosc_liczb;
    double* liczby = odczytaj_liczby(s, &ilosc_liczb);
    double* wynik = NULL;
    wynik = (double*)malloc(ilosc_liczb * sizeof(double));
    int i = 0;
    for(i = 0; i < ilosc_liczb; i++)
    {
        wynik[i] = liczby[i];
    }

    double a, b;
    int licznik_dzialan = 0;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '/')
        {
            a = wynik[licznik_dzialan];
            b = wynik[licznik_dzialan + 1];

            int j = 0;
            while(j < licznik_dzialan)
            {
                wynik[j] = liczby[j];
                j++;
            }
            a = a / b;
            wynik[licznik_dzialan] = a;
            j = j + 2;
            while(j < ilosc_liczb)
            {
                wynik[j - 1] = liczby[j];
                j++;
            }
            ilosc_liczb--;
            for(j = 0; j < ilosc_liczb; j++)
            {
                liczby[j] = wynik[j];
                //printf("%f ", liczby[j]);
            }
            //printf("\n");
        }
        if(s[i] == '+')
        {
            licznik_dzialan++;
        }
        if(s[i] == '-')
        {
            licznik_dzialan++;
        }
        if(s[i] == '*')
        {
            licznik_dzialan++;
        }
        i++;
    }

    licznik_dzialan = 0;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '/')
        {
            //licznik_dzialan++;
        }
        if(s[i] == '+')
        {
            licznik_dzialan++;
        }
        if(s[i] == '-')
        {
           licznik_dzialan++;
        }
        if(s[i] == '*')
        {
            a = wynik[licznik_dzialan];
            b = wynik[licznik_dzialan + 1];

            int j = 0;
            while(j < licznik_dzialan)
            {
                wynik[j] = liczby[j];
                j++;
            }
            a = a * b;
            wynik[licznik_dzialan] = a;
            j = j + 2;
            while(j < ilosc_liczb)
            {
                wynik[j - 1] = liczby[j];
                j++;
            }
            ilosc_liczb--;
            for(j = 0; j < ilosc_liczb; j++)
            {
                liczby[j] = wynik[j];
                //printf("%f ", liczby[j]);
            }
            //printf("\n");
        }
        i++;
    }



    licznik_dzialan = 0;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '/')
        {
            //licznik_dzialan++;
        }
        if(s[i] == '+')
        {

            licznik_dzialan++;
        }
        if(s[i] == '-')
        {
            a = wynik[licznik_dzialan];
            b = wynik[licznik_dzialan + 1];

            int j = 0;
            while(j < licznik_dzialan)
            {
                wynik[j] = liczby[j];
                j++;
            }
            a = a - b;
            wynik[licznik_dzialan] = a;
            j = j + 2;
            while(j < ilosc_liczb)
            {
                wynik[j - 1] = liczby[j];
                j++;
            }
            ilosc_liczb--;
            for(j = 0; j < ilosc_liczb; j++)
            {
                liczby[j] = wynik[j];
                //printf("%f ", liczby[j]);
            }
            //printf("\n");
        }
        if(s[i] == '*')
        {
            //licznik_dzialan++;
        }
        i++;
    }

     licznik_dzialan = 0;
    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] == '/')
        {
            //licznik_dzialan++;
        }
        if(s[i] == '+')
        {
            a = wynik[licznik_dzialan];
            b = wynik[licznik_dzialan + 1];

            int j = 0;
            while(j < licznik_dzialan)
            {
                wynik[j] = liczby[j];
                j++;
            }
            a = a + b;
            wynik[licznik_dzialan] = a;
            j = j + 2;
            while(j < ilosc_liczb)
            {
                wynik[j - 1] = liczby[j];
                j++;
            }
            ilosc_liczb--;
            for(j = 0; j < ilosc_liczb; j++)
            {
                liczby[j] = wynik[j];
                //printf("%f ", liczby[j]);
            }
            //printf("\n");
        }
        if(s[i] == '-')
        {
            //licznik_dzialan++;
        }
        if(s[i] == '*')
        {
            //licznik_dzialan++;
        }
        i++;
    }
    double W = wynik[0];
    printf("%f \n",wynik[0]);
    free(wynik);
    free(liczby);
    return W;
}

int main()
{
    printf("Kalkulator obs\210uguj\245cy dodawanie, odejmowanie, mno\276enie i dzielenie\n");

    char** dzialania = NULL;
    int liczba_dzialan;

    dzialania = wczytaj_dzialanie(dzialania, &liczba_dzialan);

    int i;
    for(i = 0; i <= liczba_dzialan; i++)
    {
        dzialania[i] = usun_spacje(dzialania[i]);
        //printf("%s \n",dzialania[i]);

    }

    for(i = 1; i <= liczba_dzialan; i++)
    {
         wykonaj_rownanie(dzialania[i]);
    }

    //odczytaj_liczby(dzialania[1]);

    return 0;
}
