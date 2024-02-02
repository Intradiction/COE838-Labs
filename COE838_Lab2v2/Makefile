CC = g++
CFLAGS = -I"C:/cygwin64/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP 
LDFLAGS = -L"C:/cygwin64/sysclibs/lib-cygwin64"
LIBS = -lsystemc

SRCS = arraymult.cpp sc_main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
EXEC = arraymult.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

CSA.o: CSA.h
	$(CC) $(CFLAGS) -MF"CSA.d" -MT"CSA.d" -o $@ $<

arraymult.o: arraymult.cpp CPA.h CSA.h
	$(CC) $(CFLAGS) -MF"CPA.d" -MT"CPA.d" -o $@ $<

sc_main.o: sc_main.cpp
	$(CC) $(CFLAGS) -MF"sc_main.d" -MT"sc_main.d" -o $@ $<

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(EXEC)
