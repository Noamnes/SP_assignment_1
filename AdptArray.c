#include<stdio.h>
#include<stdlib.h>
#include"AdptArray.h"

// i write the code with what i remember from the exercise in course system proggraming 1:

typedef struct AdptArray_ {
	int arrSize;
	PElement* elemsArr;
	COPY_FUNC cf;
	DEL_FUNC df;
	PRINT_FUNC pf;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df, PRINT_FUNC pf) {
	// setting adpt array values based on input and with some default valuse:
	PAdptArray pAdptArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pAdptArr == NULL)
		return NULL;
	pAdptArr->elemsArr = NULL;
	pAdptArr->arrSize = 0;
	pAdptArr->cf = cf;
	pAdptArr->df = df;
	pAdptArr->pf = pf;
	return pAdptArr;
}

void DeleteAdptArray(PAdptArray pAdptArray) {
	// first we free the elements then the elemsArr and then the AdptArray:
	for (int i = 0; i < pAdptArray->arrSize; i++) {
		if (pAdptArray->elemsArr[i] != NULL)
			pAdptArray->df(pAdptArray->elemsArr[i]);
	}
	if (pAdptArray->elemsArr != NULL) {
		free(pAdptArray->elemsArr);
	}
	free(pAdptArray);
}


Result SetAdptArrayAt(PAdptArray pAdptArray, int inx, PElement pElement) {
	// if inx is illegal - augment the elemsArr with realloc and put null in the new allocated indexs:
	if (inx >= pAdptArray->arrSize) {
		pAdptArray->elemsArr = (PElement*)realloc(pAdptArray->elemsArr, (inx + 1) * sizeof(PElement));
		if (pAdptArray->elemsArr == NULL)
			return FAIL;
		for (int i = pAdptArray->arrSize; i <= inx; i++) {
			pAdptArray->elemsArr[i] = NULL;
		}
		pAdptArray->elemsArr[inx] = pAdptArray->cf(pElement);
		pAdptArray->arrSize = inx + 1;
		return SUCCESS;
	}
	else { // if the inx is legal:
		if (pAdptArray->elemsArr[inx] != NULL) {
			pAdptArray->df(pAdptArray->elemsArr[inx]);
		}
		pAdptArray->elemsArr[inx] = pAdptArray->cf(pElement);
		return SUCCESS;
	}
}
//		 solution with malloc. a worse solution:

//[{book1}, {book2}, NULL]
//[{book1},    {book2},    NULL, NULL, NULL]
//Result SetAdptArrayAt(PAdptArray pAdptArray, int inx, PElement pElement) {
//	if (inx >= pAdptArray->arrSize) {
//		PElement* newElemsArr = (PElement*)calloc((inx + 1), sizeof(PElement));
//		if (newElemsArr == NULL)
//			return FAIL;
//		for (int i = 0; i < pAdptArray->arrSize; i++) {
//			if (pAdptArray->elemsArr[i] != NULL) {
//				newElemsArr[i] = pAdptArray->cf(pAdptArray->elemsArr[i]);
//				pAdptArray->df(pAdptArray->elemsArr[i]);
//			}
//		}
//		free(pAdptArray->elemsArr);
//		pAdptArray->elemsArr = newElemsArr;
//		pAdptArray->arrSize = inx + 1;
//	}
//
//	if (pAdptArray->elemsArr[inx] != NULL) {
//		pAdptArray->df(pAdptArray->elemsArr[inx]);
//	}
//	pAdptArray->elemsArr[inx] = pAdptArray->cf(pElement);
//	return SUCCESS;
//}

PElement GetAdptArrayAt(PAdptArray pAdptArray, int inx)
{
	// only if the index is legal and in the index there is an acual element we return it
	// otherwise we return null.
	if (inx < pAdptArray->arrSize)
	{
		if (pAdptArray->elemsArr[inx] != NULL)
		{
			return pAdptArray->cf(pAdptArray->elemsArr[inx]);
		}
	}
	return NULL;
}

int GetAdptArraySize(PAdptArray pAdptArray)
{
	return pAdptArray != NULL ? pAdptArray->arrSize : -1;
}

void PrintDB(PAdptArray pAdptArray)
{
	for (int i = 0; i < pAdptArray->arrSize; i++)
	{
		if (pAdptArray->elemsArr[i] != NULL)
		{
			pAdptArray->pf(pAdptArray->elemsArr[i]);
		}
	}
}


