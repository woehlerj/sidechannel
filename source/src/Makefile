CFLAGS = -std=gnu99 -O0 -g #-m32

# suppress warning
CFLAGS += -Wno-format-security

# disable executable stack
CFLAGS += -z noexecstack

# enable SSP
CFLAGS += -fstack-protector

# disable ASLR
CFLAGS += -no-pie -fno-pic

ALL := target

all: $(ALL)

target: time.o gadget.o
	$(CC) $(CFLAGS) -o $@ $^
	checksec --file=$@

time.o: time.c
	$(CC) $(CFLAGS) -c -o $@ $<

gadget.o: gadget.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(ALL) *.o

.PHONY: all clean

