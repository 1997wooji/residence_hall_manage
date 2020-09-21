
#pragma warning (disable:4996)
#include "post.h"
#include <string.h>

int PostPhoneNumberCompare(void *vp1, void *vp2)
{
	if (strcmp(((Post *)vp1)->phonenumber, ((Post *)vp2)->phonenumber) == 0)
		return 0;
	else return -1;

}

void PostMemcpy(void *p1, void *p2)
{

	strcpy(((Post *)p1)->postcode, ((Post *)p2)->postcode);
	strcpy(((Post *)p1)->phonenumber, ((Post *)p2)->phonenumber);
	((Post *)p1)->cnt = ((Post *)p2)->cnt;


}

void PostClear(void *p) 
{
	memset(((Post *)p)->postcode, 0, strlen(((Post *)p)->postcode));
	memset(((Post *)p)->phonenumber, 0, strlen(((Post *)p)->phonenumber));
}