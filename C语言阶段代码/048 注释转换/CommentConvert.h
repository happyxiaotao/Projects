#ifndef __COMMENTCONVERT_H__
#define __COMMENTCONVERT_H__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define Infilename "input.c"
#define Outfilename "output.c"

enum State
{



	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};

void DoConvertWork(FILE *fpIn, FILE *fpOut);

void CToCpp(FILE *fpIn, FILE *fpOut);

void CppToC(FILE *fpIn, FILE *fpOut);

void DoNulConvert(FILE *fpIn, FILE *fpOut);

#endif //__COMMENTCONVERT_H__