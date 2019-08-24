CC=gcc
CFLAGS+= -Wall -Wextra -Wshadow -masm=intel
LDFLAGS= -no-pie
SDIR=src
OUT=handout

TARGET=q3

SRCS=$(wildcard $(SDIR)/*.c)
OBJS=$(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $(OUT)/$@

$(SDIR)/%.o: $(SDIR)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -vf $(SRCS)/*.o $(OUT)/*

