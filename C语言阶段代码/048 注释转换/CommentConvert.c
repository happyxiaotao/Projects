#include "CommentConvert.h"
static enum State state = NUL_STATE;

void DoConvertWork(FILE *fpIn, FILE *fpOut)
{
	int ch = fgetc(fpIn);
	assert(fpIn);
	assert(fpOut);

	if (EOF == ch)
	{
		printf("%sÎª¿Õ", Infilename);
	}
	fseek(fpIn, 0, SEEK_SET);
	while (END_STATE != state)
	{
		switch (state)
		{
		case C_STATE:
			CToCpp(fpIn, fpOut);
			break;
		case CPP_STATE:
			CppToC(fpIn, fpOut);
			break;
		case NUL_STATE:
			DoNulConvert(fpIn, fpOut);
			break;
		default:
			break;
		}
	}
}

void CToCpp(FILE *fpIn, FILE *fpOut)
{
	int first = fgetc(fpIn);

	if ('*' == first)
	{
		int second = fgetc(fpIn);

		if ('/' == second)
		{
			int third = fgetc(fpIn);

			fputc('\n', fpOut);
			if ('\n' != third)
			{
				ungetc(third, fpIn);
			}
			
			state = NUL_STATE;
		}
		else if ('*' == second)
		{
			fputc('*', fpOut);
			ungetc(second, fpIn);
		}
		else
		{
			fputc(first, fpOut);
			fputc(second, fpOut);
		}
	}
	else if ('\n' == first)
	{
		fputc('\n', fpOut);
		fputc('/', fpOut);
		fputc('/', fpOut);
	}
	else
	{
		fputc(first, fpOut);
	}
}
void CppToC(FILE *fpIn, FILE *fpOut)
{
	
	int first = fgetc(fpIn);

	if ('\n' == first)
	{
		fputc('*', fpOut);
		fputc('/', fpOut);
		fputc('\n', fpOut);
		state = NUL_STATE;
	}
	else if ('/' == first)
	{
		int second = fgetc(fpIn);
		if ('*' == second)
		{
			fputc('\n', fpOut);
			fputc('/', fpOut);
			fputc('/', fpOut);
		}
		else
		{
			fputc(first, fpOut);
			ungetc(second, fpIn);
		}
	}
	else if ('*' == first)
	{
		int second = fgetc(fpIn);
		if ('/' != second)
		{
			fputc(first, fpOut);
			ungetc(second, fpIn);
		}
	}
	else if (EOF == first)
	{
		
		fputc(EOF, fpOut);
		state = END_STATE;
	}
	else
	{
		fputc(first, fpOut);
	}
	
}
void DoNulConvert(FILE *fpIn, FILE *fpOut)
{
	int first = fgetc(fpIn);

	if ('/' == first)
	{
		int second = fgetc(fpIn);
		if ('*' == second)
		{
			state = C_STATE;
			fputc('/', fpOut);
			fputc('/', fpOut);
		}
		
		else if ('/' == second)
		{
			state = CPP_STATE;
			fputc('/', fpOut);
			fputc('*', fpOut);
		}
		else
		{
			fputc(first, fpOut);
			fputc(second, fpOut);
		}
	}
	else if (EOF == first)
	{
		state = END_STATE;
	}
	else
	{
		fputc(first, fpOut);
	}	
}