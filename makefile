CPP = g++-7
CPPFLAGS = -Wall - Wextra -pedantic -g
IDIR =..crow/include

server.o: $(CPP) -I $(IDIR) $(CPPFLAGS) cache.cc server.cc -o server -pthread -lboost_system;

benchmark: $(CPP) $(CPPFLAGS) client.cc cache.h benchmark.cc -o benchmark;
