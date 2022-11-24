CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT = main
ODIR = ./obj
SDIR = ./src
OUTDIR = ./bin
LDIR = ./lib
LIBS = -lm
OBJS = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(wildcard $(SDIR)/*.c))

all : MKFOLDERS $(OUTDIR)/$(OUT) 

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OUTDIR)/main : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: 
	$(OUTDIR)/$(OUT)

MKFOLDERS :
	@if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	@if [ ! -d $(OUTDIR) ]; then mkdir $(OUTDIR); fi

clean:
	rm $(ODIR)/*.o $(OUTDIR)/*
