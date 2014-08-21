TARGET = test
OBJS   =  test.o unity_fixture.o unity.o
OBJS   += test_lib.o

VPATH = src:../share/
CFLAGS = -Wall -std=c99
CFLAGS = -std=c99
CFLAGS += -I.
CFLAGS += -I..
CFLAGS += -I../share/

CFLAGS += -Os

.SUFFIXES: .c .o

all :		$(TARGET)

run	:	$(TARGET)
		./$(TARGET)

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET)
