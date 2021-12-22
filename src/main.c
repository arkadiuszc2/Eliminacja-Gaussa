#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"


int compare_double(double a,double b)
{
    int eps=0.000001;
    double res=a-b;
    if(res<0)   res=res*(-1);

    if(res<eps) return 0;
    return 1;
}
int main(int argc, char **argv)
{ //sprawdzenie czy poprawnie dokonano push na github
    int res;
    Matrix *A = readFromFile(argv[1]);
    Matrix *b = readFromFile(argv[2]);
    Matrix *x;

    if (A == NULL)
        return -1;
    if (b == NULL)
        return -2;
    printToScreen(A);
    printToScreen(b);

    res = eliminate(A, b);
    x = createMatrix(b->r, 1);
    if (res != 0)
    {
        fprintf(stderr, "Błąd! Macierz jest osobliwa!\n");
    }
    else if (x != NULL)
    {
        res = backsubst(x, A, b);
        if (res != 0)
        {
            if (res == 1)
                fprintf(stderr, "Błąd! Wystąpiło dzielenie przez zero!");
            else if (res == 2)
                fprintf(stderr, "Błąd! Wymiary podanych macierzy są nieprawidłowe!\n");
        }
        else
        {
            printToScreen(x);
            freeMatrix(x);
        }
    }
    else
    {
        fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
    }

    freeMatrix(A);
    freeMatrix(b);

    if (argc <= 4)
    {
        printf("WYNIKI DANYCH TESTOWYCH:\n");
        char plik[64];
        char plikA[64];
        char plikb[64];
        char plikxr[64];
        char znak[2];
        int failflag=0;
        Matrix *test_check;
        for (int i = 1; i <= 4; i++)
        {
            plik[0] = '\0';
            strcat(plik, argv[3]);
            strcat(plik, "/test");
            znak[0]=(char)(i + 48);
            znak[1]='\0';
            strcat(plik,znak);

            plikA[0]='\0';
            strcat(plikA,plik);
            strcat(plikA,"/A");
            plikA[strlen(plikA)] = '\0';
            
            A = readFromFile(plikA);

            plikb[0]='\0';
            strcat(plikb,plik);
            strcat(plikb,"/b");
            plikb[strlen(plikb)] = '\0';

            b = readFromFile(plikb);

            plikxr[0]='\0';
            strcat(plikxr,plik);
            strcat(plikxr,"/xr");
            plikxr[strlen(plikxr)] = '\0';

            test_check=readFromFile(plikxr);

            if (A == NULL)
                return -1;
            if (b == NULL)
                return -2;
            printToScreen(A);
            printToScreen(b);

            res = eliminate(A, b);
            x = createMatrix(b->r, 1);
            if (res != 0)
            {
                fprintf(stderr, "Błąd! Macierz jest osobliwa!\n");
            }
            else if (x != NULL)
            {
                res = backsubst(x, A, b);
                if (res != 0)
                {
                    if (res == 1)
                        fprintf(stderr, "Błąd! Wystąpiło dzielenie przez zero!\n");
                    else if (res == 2)
                        fprintf(stderr, "Błąd! Wymiary podanych macierzy są nieprawidłowe!\n");
                }
                else
                {
                    printf("COMPARE\n");
                    printToScreen(x);
                    printToScreen(test_check);
                    printf("COMPARE\n");
                    for(int i=0;i<x->r;i++)
                    {
                        if(compare_double(x->data[i][0],test_check->data[i][0])==0)
                        {
                            fprintf(stderr,"Błąd! Wynik jest nieprawidlowy!\n");
                            failflag=1;
                            break;
                        }
                    }
                    if(failflag==0)
                    {
                        printf("Wynik jest poprawny!\n");
                    }
                    freeMatrix(x);
                }
            }
            else
            {
                fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
            }
            freeMatrix(test_check);
            freeMatrix(A);
            freeMatrix(b);
            failflag=0;
        }
    }

    return 0;
}
