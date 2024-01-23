CC = g++
CFLAGS = -I"C:/cygwin64/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP
LDFLAGS = -L"C:/cygwin64/sysclibs/lib-cygwin64"
LIBS = -lsystemc

SRCS = barrelshift.cpp flipflop.cpp sc_main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
EXEC = barrelflop.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -MF"$(@:.o=.d)" -MT"$(@:.o=.d)" -o $@ $<

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(EXEC)