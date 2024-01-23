CC = g++
CFLAGS = -I"C:/cygwin64/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP 
LDFLAGS = -L"C:/cygwin64/sysclibs/lib-cygwin64"
LIBS = -lsystemc

SRCS = alu.cpp barrelshift.cpp sc_main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
EXEC = alu.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

alu.o: alu.cpp alu.h
	$(CC) $(CFLAGS) -MF"alu.d" -MT"alu.d" -o $@ $<

barrelshift.o: barrelshift.cpp barrelshift.h
	$(CC) $(CFLAGS) -MF"barrelshift.d" -MT"barrelshift.d" -o $@ $<

sc_main.o: sc_main.cpp
	$(CC) $(CFLAGS) -MF"sc_main.d" -MT"sc_main.d" -o $@ $<

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(EXEC)
