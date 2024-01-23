RM := rm -rf

all:
	g++ -I"/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"flipflop.d" -MT"flipflop.o" -o "flipflop.o" "flipflop.cpp"
	g++ -I"/sysclibs/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"sc_main.d" -MT"sc_main.o" -o "sc_main.o" "sc_main.cpp"
	g++ -L"/sysclibs/lib-cygwin64" -o "flipflop.exe" ./flipflop.o ./sc_main.o -lsystemc

#clean:
#    rm -f flipflop.d flipflop.o sc_main.d sc_main.o
#    rm -f flipflop.exe
clean:
	-$(RM) flipflop.d flipflop.o sc_main.d sc_main.o flipflop.exe
	-@echo ' '