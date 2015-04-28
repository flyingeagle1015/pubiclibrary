#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

/**
 *  base64_encode - Encode the string into base64 encoding
 *  @origstr: data to encode
 *  @len:     data length
 *  @enstr:   encoded data
 *  @size:    size of the encoded data
 *
 *  Returns -1 if paramers are invalid, or 0 if success.
 */
int base64_encode(const char *src, unsigned len, char *base64, unsigned size);

/**
 *  base64_decode - Decode the base64 encoding
 *  @origstr: the base64 encoding data
 *  @len:     data length
 *  @destr:   the string has been decoded 
 *  @size:    size of the string
 *
 *  Returns -1 if paramers are invalid, or 0 if success.
 */
int base64_decode(const char *base64, unsigned len, char *dst, unsigned size);

#endif /* BASE64_H_INCLUDED */
