#ifndef URLCODE_H_INCLUDED
#define URLCODE_H_INCLUDED

/**
 *  urlencode - Encode the string into the URL encoding
 *  @origstr: data to encode
 *  @len:     data length
 *  @enstr:   encoded data
 *  @size:    size of the encoded data
 *
 *  Returns -1 if paramers are invalid, or the size of buffer needed.
 */
int urlencode(const char *origstr, unsigned len, char *enstr, unsigned size);

/**
 *  urldecode - Decode the URL encoding
 *  @origstr: the URL encoding data
 *  @len:     data length
 *  @destr:   the string has been decoded 
 *  @size:    size of the string
 *
 *  Returns -1 if paramers are invalid, or the size of buffer needed.
 */
int urldecode(const char *origstr, unsigned len, char *destr, unsigned size);

#endif /* URLCODE_H_INCLUDED */
