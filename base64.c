/**
 *    base64 Table
 * 
 *  0  A   16 Q   32 g   48 w
 *	1  B   17 R   33 h   49 x
 *	2  C   18 S   34 i   50 y
 *	3  D   19 T   35 j   51 z
 *	4  E   20 U   36 k   52 0
 *	5  F   21 V   37 l   53 1
 *	6  G   22 W   38 m   54 2
 *	7  H   23 X   39 n   55 3
 *	8  I   24 Y   40 o   56 4
 *	9  J   25 Z   41 p   57 5
 *	10 K   26 a   42 q   58 6
 *	11 L   27 b   43 r   59 7
 *	12 M   28 c   44 s   60 8
 *	13 N   29 d   45 t   61 9
 *	14 O   30 e   46 u   62 +
 *	15 P   31 f   47 v   63 /
 *
 * base64 encoding:
 *
 * original text:
 *   abcd
 *	 61 62 63 64 (hexadecimal)
 *	 01100001 01100010 01100011 01100100
 *	 00011000 00010110 00001001 00100011 00011001 00000000
 *   24 22 09 35 25 00 (decimal base)
 *	 Y  W  J  j  Z  A
 *	 result: YWJjZA==
 *  
 * base64 decoding:
 *	 YWJjZA==
 *   24 22 09 35 25 0  (decimal base)
 *	 00011000 00010110 00001001 00100011 00011001 00000000
 *	 01100001 01100010 01100011 01100100 0000
 *	 61 62 63 64
 *	 result: abcd
 **/

#include "base64.h"

static const char BASE64[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char BASEMAP[128] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, 64, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};

int base64_encode(const char *src, unsigned len, char *base64, unsigned size)
{
	register unsigned tmpval = 0;
	char *p64 = base64;
	unsigned char *psrc = (unsigned char*)src;
	
	if (size < ((len << 2) / 3 + 4)) {
		return -1;
	}

	for (; 3 <= len; len -= 3) {
		tmpval = (*psrc << 16) | (*(psrc + 1) << 8) | (*(psrc + 2));
		*p64++ = BASE64[(tmpval & 0x00FC0000) >> 18];
		*p64++ = BASE64[(tmpval & 0x0003F000) >> 12];
		*p64++ = BASE64[(tmpval & 0x00000FC0) >> 6];
		*p64++ = BASE64[(tmpval & 0x0000003F) >> 0];
		psrc += 3;
	}
	
	/* process the rest data */
	if(1 == len) {
		*p64++ = BASE64[((*(psrc)) >> 2) & 0x3F];
		*p64++ = BASE64[((*(psrc)) & 0x3) << 4];
		*p64++ = '=';
		*p64++ = '=';
	} else if(2 == len) {
		*p64++ = BASE64[((*(psrc)) >> 2) & 0x3F];
		*p64++ = BASE64[(((*(psrc)) & 0x3) << 4) | ((*(psrc + 1)) >> 4)];
		*p64++ = BASE64[((*(psrc + 1) & 0xF) << 2)];
		*p64++ = '=';
	}

	*p64 = '\0';
	return 0;
}

int base64_decode(const char *base64, unsigned len, char *dst, unsigned size)
{
	int i;
	int index;
	unsigned tmpval = 0;
	char *pbuf = dst;
	unsigned char* psrc = (unsigned char*)base64;

	if (size < (len - (len >> 2))) {
		return -1;
	}
	
	while (4 <= len && 64 != index) {
		for (i = 0; i < 4; i++) {
			if ((index = BASEMAP[*psrc++]) < 0) {
				goto end;
			}
			
			/*
			 * it is slower than if ... else ...
			 * tmpval = ((tmpval << 6) | (index & 0x3F));
			*/
			if (64 == index) {
				tmpval = (tmpval << 6);
			} else {
				tmpval = ((tmpval << 6) | index);
			}
			len--;
		}
		
		switch (i) {
		case 4:
			*pbuf++ = ((tmpval >> 16) & 0xFF);
		case 3:
			*pbuf++ = ((tmpval >> 8) & 0xFF);
		case 2:
			*pbuf++ = (tmpval & 0xFF);
			break;
		default:
			break;
		}
	}
	
end:
	*pbuf = '\0';
	return len;
}
