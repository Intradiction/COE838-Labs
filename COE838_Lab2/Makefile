
all:
	g++ -I"C:\cygwin64\sysclibs\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"sc_main.d" -MT"sc_main.o" -o "sc_main.o" "sc_main.cpp"
	g++ -L"C:/cygwin64/sysclibs/lib-cygwin64" -o "arraymultiplier.exe" ./sc_main.o -lsystemc
