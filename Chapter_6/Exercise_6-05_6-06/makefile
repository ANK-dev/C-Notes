CC = gcc

TARGET = Exercise_6-05_6-06

SDIR = src

IDIR = headers
_DEPS = getword.h struct_proc.h ungets.h

ODIR = obj
_OBJ = $(TARGET).o getword.o struct_proc.o ungets.o

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

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o ../out/$@.out $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
