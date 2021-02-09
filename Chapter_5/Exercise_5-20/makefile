CC = gcc
CFLAGS = \
	-ansi \
	-pedantic \
	-Wall \
	-Wextra \
	-Werror \
	-Wfloat-equal \
	-Wundef \
	-Wshadow \
	-Wpointer-arith \
	-Wcast-align \
	-Wstrict-overflow=5 \
	-Wwrite-strings \
	-Waggregate-return \
	-Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code \
	-Wformat=2 \
	-Wcast-qual

IDIR = ./headers
ODIR = ./obj

_DEPS = dcl.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = dcl.o dcl_dirdcl.o getch_ungetch.o gettoken.o parmdcl.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Exercise_5-20_dcl: $(OBJ)
	$(CC) -o ../out/$@.out $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
