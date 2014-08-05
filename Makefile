all : main libcache.so libuser.so

CC = gcc
CFLAGS = -g -Wall

main : main.o libcache.so
	$(CC) -o $@ $< -L. -ldl -lcache
main.o : main.c

libcache.so : cache.o table.o
	$(CC) -shared -o $@ $^
cache.o : cache.c cache.h table.h
	$(CC) -fPIC $(CFLAGS) -c $<
table.o : table.c table.h
	$(CC) -fPIC $(CFLAGS) -c $<

libuser.so : user.o
	$(CC) -shared -o $@ $<
user.o : user.c user.h
	$(CC) -fPIC $(CFLAGS) -c $<

clean :
	-rm main *.so *.o
