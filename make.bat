REM logic
lcc -c dev/main.c -o main.o
REM build
lcc -Wl-yt1 -Wl-yo4 -Wl-ya0 main.o -o rom/NuclearHead.gb
REM clean
del *.o *.lst
pause