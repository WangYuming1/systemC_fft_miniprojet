# Makefile for C implementation
# Author : Pierre-Henri Horrein

CC=gcc

SRCDIR=.
INCDIR=.
OBJDIR=.

SRC = $(wildcard $(SRCDIR)/*.c)
TMP_OBJ = $(subst .c,.o,$(SRC))
NEW_OBJ = $(subst $(SRCDIR)/,$(OBJDIR)/,$(TMP_OBJ))
CFLAGS = -c -g -std=c99

all : test_fft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $<
test_fft : $(NEW_OBJ)
	$(CC) -I$(INCDIR) -o test_fft $(NEW_OBJ)

clean: 
	rm -f $(NEW_OBJ) test_fft

