/*
__________________________________________________________________________________

					PolynomialCalculator (core)


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


TO DO :

- Find roots of a polynomial.
__________________________________________________________________________________			*/


#include <malloc.h>

typedef struct polynomialNode Node;

struct polynomialNode {

	float
		fCoeff,
		fExp
	;

	Node *nextTerm;
};

Node* createTerm(float coeff, float exp) {

	Node *newTerm = (Node *)malloc(sizeof(Node));
	if(newTerm == NULL)
		return NULL;

	newTerm->fCoeff = coeff;
	newTerm->fExp = exp;

	newTerm->nextTerm = NULL;

	return newTerm;
}


void insertTerm(Node **polynomial, Node *term) { //inserts in descending order of degree.

	if(*polynomial == NULL)
		*polynomial = term;
	else {

		Node
			*tempPolynomial = *polynomial,
			*nodePos		= NULL
		;
		if((*polynomial)->fExp < term->fExp) {

			term->nextTerm = *polynomial;
			*polynomial = term;
		} else {

			while(tempPolynomial != NULL) {

				if(tempPolynomial->fExp == term->fExp) {

					tempPolynomial->fCoeff += term->fCoeff;
					break;
				}
				else if(term->fExp < tempPolynomial->fExp)
					nodePos = tempPolynomial;
				tempPolynomial = tempPolynomial->nextTerm;
			}
			if(tempPolynomial == NULL) {

				term->nextTerm = nodePos->nextTerm;
				nodePos->nextTerm = term;

			}
		}
	}
}

Node* addPolynomial(Node *polynomialA, Node *polynomialB) {

	Node *retPolynomial = NULL;
	while(polynomialA != NULL && polynomialB != NULL) {

		if(polynomialA->fExp == polynomialB->fExp) {

			insertTerm(&retPolynomial, createTerm(polynomialA->fCoeff + polynomialB->fCoeff, polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
			polynomialB = polynomialB->nextTerm;
		} else if(polynomialA->fExp > polynomialB->fExp) {

			insertTerm(&retPolynomial, createTerm(polynomialA->fCoeff, polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
		} else {

			insertTerm(&retPolynomial, createTerm(polynomialB->fCoeff, polynomialB->fExp));
			polynomialB = polynomialB->nextTerm;
		}
	}
	if(polynomialA == NULL) {

		while(polynomialB != NULL) {

			insertTerm(&retPolynomial, createTerm(polynomialB->fCoeff, polynomialB->fExp));
			polynomialB = polynomialB->nextTerm;
		}
	} 
	if(polynomialB == NULL) {

		while(polynomialA != NULL) {

			insertTerm(&retPolynomial, createTerm(polynomialA->fCoeff, polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
		}
	}
	return retPolynomial;
}

Node* subPolynomial(Node *polynomialA, Node *polynomialB) {

	Node *retPolynomial = NULL;
	while(polynomialA != NULL && polynomialB != NULL) {

		if(polynomialA->fExp == polynomialB->fExp) {

			insertTerm(&retPolynomial, createTerm(polynomialA->fCoeff - polynomialB->fCoeff, polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
			polynomialB = polynomialB->nextTerm;
		} else if(polynomialA->fExp > polynomialB->fExp) {

			insertTerm(&retPolynomial, createTerm(-(polynomialA->fCoeff), polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
		} else {

			insertTerm(&retPolynomial, createTerm(-(polynomialB->fCoeff), polynomialB->fExp));
			polynomialB = polynomialB->nextTerm;
		}
	}
	if(polynomialA == NULL) {

		while(polynomialB != NULL) {

			insertTerm(&retPolynomial, createTerm(-(polynomialB->fCoeff), polynomialB->fExp));
			polynomialB = polynomialB->nextTerm;
		}
	} 
	if(polynomialB == NULL) {

		while(polynomialA != NULL) {

			insertTerm(&retPolynomial, createTerm(-(polynomialA->fCoeff), polynomialA->fExp));
			polynomialA = polynomialA->nextTerm;
		}
	}
	return retPolynomial;
}

Node* multiplyPolynomial(Node *polynomialA, Node *polynomialB) {

	Node 
		*retPolynomial = NULL,
		*tempPolynomial = polynomialB
	;
	while(polynomialA != NULL) {

		while(tempPolynomial != NULL) {

			insertTerm(&retPolynomial, createTerm(polynomialA->fCoeff * tempPolynomial->fCoeff, polynomialA->fExp + tempPolynomial->fExp));
			tempPolynomial = tempPolynomial->nextTerm;
		}
		polynomialA = polynomialA->nextTerm;
		tempPolynomial = polynomialB;
	}
	return retPolynomial;
}


int displayPolynomial(Node *polynomial) {

	if(polynomial == NULL)
		return 0;
	else {

		Node *tempNode = polynomial;
		float
			fDecimalCoeff, 	//To find the decimal part value of coeffcieint. If it's > 0.0, coefficient will be printed as a float, else as an integer only.
			fDecimalExp		//To find the decimal part value of exponent. If it's > 0.0, exponent will be printed as a float, else as an integer only.
		;
		while(tempNode != NULL) {

			fDecimalCoeff = tempNode->fCoeff - (int)tempNode->fCoeff;
			if(tempNode->fExp != 0.0) {

				fDecimalExp = tempNode->fExp - (int)tempNode->fExp;

				if(fDecimalCoeff && fDecimalExp)
					printf("%0.2fx^%0.2f ", tempNode->fCoeff, tempNode->fExp);
				else if(fDecimalCoeff && !fDecimalExp)
					printf("%0.2fx^%d ", tempNode->fCoeff, (int)tempNode->fExp);
				else if(!fDecimalCoeff && fDecimalExp)
					printf("%dx^%0.2f ", (int)tempNode->fCoeff, tempNode->fExp);
				else
					printf("%dx^%d ", (int)tempNode->fCoeff, (int)tempNode->fExp);
			} else {

				if(fDecimalCoeff)
					printf("%0.2f ", tempNode->fCoeff);
				else
					printf("%d ", (int)tempNode->fCoeff);
			}
			if(tempNode->nextTerm != NULL)
				printf("+ ");

			tempNode = tempNode->nextTerm;
		}
	}
	return 1;
}
