CC = gcc

IDIR = headers
ODIR = obj
SDIR = src
TARGET = Exercise_6-03

CFLAGS = \
	-I. \
	-g \
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

_DEPS = getword.h linklist.h tree.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(TARGET).o getword.o linklist.o tree.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o ../out/$@.out $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
