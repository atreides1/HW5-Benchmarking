CXX = g++-7
CXXFLAGS = -Wall - Wextra -pedantic -g
IDIR =..crow/include

server: $(CXX) -I $(IDIR) $(CXXFLAGS) cache.cc server.cc -o server -pthread -lboost_system;
       
benchmark: $(CXX) $(CXXFLAGS) client.cc cache.h benchmark.cc -o benchmark;

       
       
