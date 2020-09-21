#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include "timecheck.h"

int timecheck(TimeCheck * today, FILE *datep)
{
	
	if (fscanf(datep, "%s %s %s\n", today->date, today->hour, today->min) == EOF)
		return 0;
	else return 1;


}