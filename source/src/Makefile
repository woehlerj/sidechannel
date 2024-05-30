CFLAGS = -std=gnu99 -O0 -g #-m32

# supress warning
CFLAGS += -Wno-format-security

# enable executable stack
# CFLAGS += -z execstack

# enable SSP
CFLAGS += -fstack-protector

# disable ASLR
CFLAGS += -no-pie -fno-pic

ALL := target

all: $(ALL)

target: time.c
	$(CC) $(CFLAGS) -o $@ $<
	checksec --file=$@

clean:
	rm -f $(ALL)

.PHONY: all clean
