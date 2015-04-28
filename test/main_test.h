#ifndef MAIN_TEST_H_INCLUDED
#define MAIN_TEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* print message */
#define INFO(fmt, arg...) do { fprintf(stdout, "INFO "fmt, ##arg); } while (0)
/* print program error */
#define WARN(fmt, arg...) do { fprintf(stderr, "WARN "fmt, ##arg); } while (0)
/* print system error */
#define ERR(fmt, arg...) do { fprintf(stderr, "ERR "fmt, ##arg); exit(1); } while (0)

#endif /* MAIN_TEST_H_INCLUDED */
