#include "urlcode.h"
#include "main_test.h"

struct {
	char *orig;       /* original string */
	char *encode;     /* expect encode string */
	char *decode;     /* expect decode string */
	unsigned ensize;  /* encode buffer size */
	unsigned desize;  /* decode buffer size */
	int enres;        /* expect encode result */
	int deres;        /* expect decode result */
}s_urlcode_cases[] = {
	{NULL, NULL, NULL, 0, 0, -1, -1},     /* original buffer is null */
	{"abc", "abc", "abc", 0, 0, -1, -1},  /* encode or decode buffer is null */
	{"abc", "ab", "ab", 3, 3, 4, 3},      /* encode buffer is fewer than needed */
	{"abc", "abc", "ab", 4, 3, 4, 4},     /* decode buffer is fewer than needed */
	{"abc", "abc", "abc", 4, 4, 4, 4},    /* ASCII */
	{"a c", "a+c", "a c", 4, 4, 4, 4},    /* ASCII, space */
	{"ab+=cd", "ab%2b%3dc", "ab+=c", 10, 6, 11, 6},    /* ASCII, space, special characters */
	{"ab+=cd", "ab%2b%3dcd", "ab+=cd", 11, 7, 11, 7},    /* ASCII, space, special characters */
};

int main(int argc, char *argv[])
{
	int i;
	int enres, deres;
	char *enbuf = NULL;
	char *debuf = NULL;
	int erc = 0, drc = 0;
	
	for (i = 0; i < ARRAY_SIZE(s_urlcode_cases); i++) {
		if (s_urlcode_cases[i].ensize) {
			enbuf = malloc(s_urlcode_cases[i].ensize);
			if (!enbuf) {
				ERR("CASE [%d]: malloc failed, enbuf=%p/%u\n", i, enbuf, s_urlcode_cases[i].ensize);
			}
		}
		if (s_urlcode_cases[i].desize) {
			debuf = malloc(s_urlcode_cases[i].desize);
			if (!debuf) {
				ERR("CASE [%d]: malloc failed, debuf=%p/%u\n", i, debuf, s_urlcode_cases[i].desize);
			}
		}
		
		enres = urlencode(s_urlcode_cases[i].orig, 
			(s_urlcode_cases[i].orig ? strlen(s_urlcode_cases[i].orig) : 0),
			enbuf, s_urlcode_cases[i].ensize);
		deres = urldecode(s_urlcode_cases[i].encode,
			(s_urlcode_cases[i].encode ? strlen(s_urlcode_cases[i].encode) : 0),
			debuf, s_urlcode_cases[i].desize);
		if (enres != s_urlcode_cases[i].enres ||
			(s_urlcode_cases[i].encode && enbuf && strcasecmp(s_urlcode_cases[i].encode, enbuf))) {
			erc++;
			WARN("CASE [%d]: encode failed, enbuf='%s', expect enbuf='%s', res=%d, expect res=%d\n",
				i, enbuf, s_urlcode_cases[i].encode, enres, s_urlcode_cases[i].enres);
		}
		
		if (deres != s_urlcode_cases[i].deres ||
			(s_urlcode_cases[i].decode && debuf && strcasecmp(s_urlcode_cases[i].decode, debuf))) {
			drc++;
			WARN("CASE [%d]: decode failed, debuf='%s', expect debuf='%s', res=%d, expect res=%d\n",
				i, debuf, s_urlcode_cases[i].decode, deres, s_urlcode_cases[i].deres);
		}
		
		free(enbuf);
		free(debuf);
	}
	
	INFO("[%s]: All Case [%d], encode failed [%d], decode failed [%d]\n", __FILE__, i, erc, drc);
	
	return 0;
}
