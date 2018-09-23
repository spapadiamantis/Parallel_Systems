CC = mpicc
CPPFLAGS = -g
HEADERS = mpiFunctions.h
SRC =  convolution.c mpiFunctions.c
OBJS =  convolution.o mpiFunctions.o

all: convolution

%.o: %.c $(HEADERS)
	$(CC) -c $< $ $
	
convolution: $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS)