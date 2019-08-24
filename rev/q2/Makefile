CC=gcc
CFLAGS= -Wall -Wextra -Wshadow -O3 -funroll-loops
SDIR=src
OUT=handout

TARGET=q2

SRCS=$(wildcard $(SDIR)/*.c)
OBJS=$(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $(OUT)/$@
	strip --strip-all $(OUT)/$@

$(SDIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -vf $(SRCS)/*.o $(OUT)/*

