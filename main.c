/*
__________________________________________________________________________________

				PolynomialCalculator - v1.0 BETA

NOTE:
"main()" part for now is only for testing basic
polynomial functions. This program is currently work 
in progress.


Copyright (c) 2017 Akshay Mohan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
__________________________________________________________________________________	*/


#include <stdio.h>
#include "main.h"
#include <conio.h> //Comment if you're using Linux.

Node 
	*g_polynomialP = NULL,
	*g_polynomialQ = NULL
;


int main() {

	Node *polynomialTerm;

	/*insertTerm(&g_polynomialP, createTerm(5, 1));
	insertTerm(&g_polynomialP, createTerm(3, 0));

	insertTerm(&g_polynomialQ, createTerm(6, 1));
	insertTerm(&g_polynomialQ, createTerm(7, 0));*/

	insertTerm(&g_polynomialP, createTerm(6, 2));
	insertTerm(&g_polynomialP, createTerm(7, 1));
	insertTerm(&g_polynomialP, createTerm(13, 0));

	insertTerm(&g_polynomialQ, createTerm(3, 2));
	insertTerm(&g_polynomialQ, createTerm(8, 1));
	insertTerm(&g_polynomialQ, createTerm(9, 0));

	printf("P = ");
	displayPolynomial(g_polynomialP);

	printf("\nQ = ");
	displayPolynomial(g_polynomialQ);

	printf("\nP + Q = R\n");
	printf("R = ");

	polynomialTerm = addPolynomial(g_polynomialP, g_polynomialQ);
	displayPolynomial(polynomialTerm);

	free(polynomialTerm);

	printf("\nA = ");
	displayPolynomial(g_polynomialP);

	printf("\nB = ");
	displayPolynomial(g_polynomialQ);

	printf("\nA * B = ");
	polynomialTerm = multiplyPolynomial(g_polynomialP, g_polynomialQ);
	displayPolynomial(polynomialTerm);

	free(polynomialTerm);

	printf("\nA-B = ");
	polynomialTerm = subPolynomial(g_polynomialP, g_polynomialQ);
	displayPolynomial(polynomialTerm);

	#ifdef getch
		getch();
	#endif
	return 0;
}