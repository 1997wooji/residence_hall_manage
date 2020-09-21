#pragma once

typedef struct _post
{
	char phonenumber[16];
	char postcode[5];
	int cnt;
}Post;

int PostPhoneNumberCompare(void *, void *);
void PostMemcpy(void *, void *);
void PostClear(void *);