TARGET = test
OBJS   =  test.o unity_fixture.o unity.o
OBJS   += test_lib.o

CFLAGS = -Wall -std=c99
CFLAGS = -std=c99
CFLAGS += -I.
CFLAGS += -I..

CFLAGS += -Os

.SUFFIXES: .c .o

run	:	$(TARGET)
		./$(TARGET)

all :		$(TARGET)

$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)

.c.o :		$<
		$(CC) -c $(CFLAGS) $<

clean :
		rm -f $(OBJS) $(TARGET)
