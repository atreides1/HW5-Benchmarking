CPP = g++-7
CPFLAGS = -Wall - Wextra -pedantic -g

server:
       $(CPP) -I../crow/include CPFLAGS cache.cc server.cc -o server -pthread -lboost_system;
       
benchmark:
       $(CPP) client.cc cache.h benchmark.cc -o benchmark;

       
       
