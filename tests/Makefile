# CFLAGS += -Wall -Wextra -pedantic -Werror
# CFLAGS += -Wall -Wextra -pedantic
# CFLAGS += -Wmissing-declarations -g
# CFLAGS += -Wmissing-prototypes
# CFLAGS += -Wstrict-prototypes
CFLAGS += -I../include

LDFLAGS = -lm

PROGRAMS = unit

all: ${PROGRAMS}

unit: unit.o ../src/message.o ../src/basic_id.o ../src/location.o ../src/operator_id.o

test: unit
	./unit

%.o: %.c
	${CC} -c -o $@ ${CFLAGS} $<

%: %.o
	${CC} -o $@ ${LDFLAGS} $^

*.o: Makefile
*.o: greatest.h
clean:
	rm -f ${PROGRAMS} ${PROGRAMSPP} *.o *.core ../src/*.o

