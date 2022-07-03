CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT = main
ODIR = ./obj
SDIR = ./src
OUTDIR = ./bin
LDIR = ./lib
LIBS = -lm
OBJS = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(wildcard $(SDIR)/*.c))

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OUTDIR)/main : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	$(OUTDIR)/$(OUT)

clean:
	rm $(ODIR)/*.o $(OUTDIR)/*
