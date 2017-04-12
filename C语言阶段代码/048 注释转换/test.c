#include "CommentConvert.h"

int main()
{
	FILE *fpRead = fopen(Infilename, "r");
	FILE *fpWrite = fopen(Outfilename, "w");

	if (NULL == fpRead)
	{
		perror(Infilename);
		exit(0);
	}
	if (NULL == fpWrite)
	{
		fclose(fpRead);
		perror(Outfilename);
		exit(0);
	}

	DoConvertWork(fpRead, fpWrite);
	fclose(fpRead);
	fclose(fpWrite);

	return 0;
}