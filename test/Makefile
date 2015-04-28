DEBUG = y
INCPATH = -I../
LIBPATH =

CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS =
CFLAGS += $(INCPATH)
LDFLAGS += $(LIBPATH)

ifneq ($(DEBUG), y)
CFLAGS += -O2
else
CFLAGS += -g -O0 -DDEBUG
endif

DESTDIR = bin
ROOTFS = 

# list of generated object files
URLCODE_OBJS = urlcode_test.o ../urlcode.o
BASE64_OBJS = base64_test.o ../base64.o

URLCODE_SRCS = $(URLCODE_OBJS:.o=.c)
BASE64_SRCS = $(BASE64_OBJS:.o=.c)

URLCODE_DEPS := $(URLCODE_OBJS:.o=.d)
BASE64_DEPS := $(BASE64_OBJS:.o=.d)

# program executables. 
URLCODE = urlcode_test
BASE64 = base64_test

.PHONY: deps clean clean_libs libs

# top-level rule, to compile everything.
all: $(URLCODE) $(BASE64)

$(URLCODE):$(URLCODE_OBJS)
	$(CC) $(URLCODE_OBJS) $(CFLAGS) $(LDFLAGS) -o $(URLCODE)

$(BASE64):$(BASE64_OBJS)
	$(CC) $(BASE64_OBJS) $(CFLAGS) $(LDFLAGS) -o $(BASE64)

clean:
	rm -f $(URLCODE) $(URLCODE_OBJS) $(URLCODE_DEPS)
	rm -f $(BASE64) $(BASE64_OBJS) $(BASE64_DEPS)

clean_deps:
	$(URLCODE_DEPS)
	$(BASE64_DEPS)
	
deps: $(URLCODE_SRC)
	$(CC) -MD -E $(URLCODE_SRCS) $(CFLAGS) >/dev/null
	$(CC) -MD -E $(BASE64_SRCS) $(CFLAGS) >/dev/null

-include $(URLCODE_DEPS)
-include $(BASE64_DEPS)
