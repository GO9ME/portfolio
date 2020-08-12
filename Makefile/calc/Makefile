CC = gcc

TARGET_SRV = server
OBJS_SRV = op_server.o error.o calc.o

TARGET_CLN = client
OBJS_CLN = op_client.o error.o

#LDFLAGS =-D_REENTRANT -pthread

all : $(TARGET_SRV) $(TARGET_CLN)

$(TARGET_SRV) : $(OBJS_SRV)
	$(CC) -o $@ $^
$(TARGET_CLN) : $(OBJS_CLN)
	$(CC) -o $@ $^

.c.o : 
	$(CC) -c -o $@ $< 
clean : 
	rm -f *.o $(TARGET_SRV) $(TARGET_CLN)
