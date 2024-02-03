CC = g++
CFLAGS = -I"C:/cygwin64/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP 
LDFLAGS = -L"C:/cygwin64/sysclibs/lib-cygwin64"
LIBS = -lsystemc

SRCS = functions.cpp fdct.cpp idct.cpp sc_main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
EXEC = sc_jpeg.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

functions.o: functions.cpp functions.h
	$(CC) $(CFLAGS) -MF"functions.d" -MT"functions.d" -o $@ $<

fdct.o: fdct.cpp fdct.h
	$(CC) $(CFLAGS) -MF"fdct.d" -MT"fdct.d" -o $@ $<

idct.o: idct.cpp idct.h
	$(CC) $(CFLAGS) -MF"idct.d" -MT"idct.d" -o $@ $<

sc_main.o: sc_main.cpp
	$(CC) $(CFLAGS) -MF"sc_main.d" -MT"sc_main.d" -o $@ $<

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(EXEC)
