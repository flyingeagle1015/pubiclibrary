#include "base64.h"
#include "main_test.h"

struct {
	char *orig;       /* original string */
	char *encode;     /* expect encode string */
	char *decode;     /* expect decode string */
	unsigned ensize;  /* encode buffer size */
	unsigned desize;  /* decode buffer size */
	int enres;        /* expect encode result */
	int deres;        /* expect decode result */
}s_base64_cases[] = {
	{"abc", "YWJj", "abc", 9, 4, 0, 0},    /* no rest data */
	{"abcdef", "YWJjZGVm", "abcdef", 12, 8, 0, 0},    /* no rest data */
	{"abcexpect decode result def", "YWJjZXhwZWN0IGRlY29kZSByZXN1bHQgZGVm", "abcexpect decode result def", 50, 28, 0, 0},    /* no rest data */
	{"a", "YQ==", "a", 9, 6, 0, 0},    /* have rest data */
	{"ab", "YWI=", "ab", 9, 6, 0, 0},    /* have rest data */
	{"abcd", "YWJjZA==", "abcd", 9, 6, 0, 0},    /* have rest data */
	{"abcde", "YWJjZGU=", "abcde", 12, 6, 0, 0},    /* have rest data */
};

int main(int argc, char *argv[])
{
	int i;
	int enres, deres;
	char *enbuf = NULL;
	char *debuf = NULL;
	int erc = 0, drc = 0;
	
	for (i = 0; i < ARRAY_SIZE(s_base64_cases); i++) {
		if (s_base64_cases[i].ensize) {
			enbuf = malloc(s_base64_cases[i].ensize);
			if (!enbuf) {
				ERR("CASE [%d]: malloc failed, enbuf=%p/%u\n", i, enbuf, s_base64_cases[i].ensize);
			}
		}
		if (s_base64_cases[i].desize) {
			debuf = malloc(s_base64_cases[i].desize);
			if (!debuf) {
				ERR("CASE [%d]: malloc failed, debuf=%p/%u\n", i, debuf, s_base64_cases[i].desize);
			}
		}
		
		enres = base64_encode(s_base64_cases[i].orig, 
			(s_base64_cases[i].orig ? strlen(s_base64_cases[i].orig) : 0),
			enbuf, s_base64_cases[i].ensize);
		deres = base64_decode(s_base64_cases[i].encode,
			(s_base64_cases[i].encode ? strlen(s_base64_cases[i].encode) : 0),
			debuf, s_base64_cases[i].desize);
		if (enres != s_base64_cases[i].enres ||
			(s_base64_cases[i].encode && enbuf && strcasecmp(s_base64_cases[i].encode, enbuf))) {
			erc++;
			WARN("CASE [%d]: encode failed, enbuf='%s', expect enbuf='%s', res=%d, expect res=%d\n",
				i, enbuf, s_base64_cases[i].encode, enres, s_base64_cases[i].enres);
		}
		if (deres != s_base64_cases[i].deres ||
			(s_base64_cases[i].decode && debuf && strcasecmp(s_base64_cases[i].decode, debuf))) {
			drc++;
			WARN("CASE [%d]: decode failed, debuf='%s', expect debuf='%s', res=%d, expect res=%d\n",
				i, debuf, s_base64_cases[i].decode, deres, s_base64_cases[i].deres);
		}
		
		free(enbuf);
		free(debuf);
	}
	
	INFO("[%s]: All Case [%d], encode failed [%d], decode failed [%d]\n", __FILE__, i, erc, drc);
	
	return 0;
}
