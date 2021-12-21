#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>

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
                fprintf(stderr, "Błąd! Wymiary podanych macierzy są nieprawidłowe!\n");
            else if (res == 2)
                fprintf(stderr, "Błąd! Wystąpiło dzielenie przez zero!");
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

    return 0;
}
