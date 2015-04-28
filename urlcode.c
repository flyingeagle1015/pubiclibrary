#include <ctype.h>

#include "urlcode.h"

static int url_htoi(const char *s)
{
    int value;
    int c;

    c = ((const unsigned char *)s)[0];
    if (isupper(c)) {
        c = tolower(c);
    }
    value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

    c = ((const unsigned char *)s)[1];
    if (isupper(c)) {
        c = tolower(c);
    }
    value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

    return (value);
}

int urlencode(const char *origstr, unsigned len, char *enstr, unsigned size)
{
    unsigned dlen = 0;
    unsigned char c;
    unsigned char *to;
    unsigned char const *from, *end;
    unsigned char hexchars[] = "0123456789ABCDEF";

    if (!origstr || !enstr || len <= 0 || len > size) {
        return -1;
    }

    from = (unsigned char *)origstr;
    end = (unsigned char *)origstr + len;
    to = (unsigned char *)enstr;

    while (from < end) {
        c = *from++;

        if (c == ' ') {
            if (++dlen < size) *to++ = '+';
        } else if ((c < '0' && c != '-' && c != '.') ||
            (c < 'A' && c > '9') ||
            (c > 'Z' && c < 'a' && c != '_') ||
            (c > 'z')) {
            if ((dlen += 3) < size) {
                to[0] = '%';
                to[1] = hexchars[c >> 4];
                to[2] = hexchars[c & 15];
                to += 3;
            }
        } else {
            if (++dlen < size) *to++ = c;
        }
    }
    *to = 0;

    return (dlen + 1);
}

int urldecode(const char *origstr, unsigned len, char *destr, unsigned size)
{
    unsigned dlen = 0;
    char *dest = destr;
    const char *data = origstr;
    
    if (!origstr || !destr || len <= 0) {
        return -1;
    }

    while (len--) {
        if (*data == '+') {
            if (++dlen < size) *dest = ' ';
        }
        else if (*data == '%' && len >= 2 && isxdigit((int) *(data + 1))
            && isxdigit((int) *(data + 2))) {
                if (++dlen < size) *dest = (char) url_htoi(data + 1);
                data += 2;
                len -= 2;
        } else {
            if (++dlen < size) *dest = *data;
        }
        data++;
        dest++;
    }
    *dest = '\0';

    return (dlen + 1);
}
