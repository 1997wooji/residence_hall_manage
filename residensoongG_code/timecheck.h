#pragma once
#include <stdio.h>

typedef struct _time {

	char date[9];
	char hour[3];
	char min[3];

}TimeCheck;

int timecheck(TimeCheck * today, FILE *datep);