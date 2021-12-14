#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv) {                       //sprawdzenie czy poprawnie dokonano push na github
        int res;
        Matrix * A = readFromFile(argv[1]);
        Matrix * b = readFromFile(argv[2]);
        Matrix * x;

        if (A == NULL) return -1;
        if (b == NULL) return -2;
        printToScreen(A);
        printToScreen(b);

        res = eliminate(A,b);
        printToScreen(A);

	return 0;

}
