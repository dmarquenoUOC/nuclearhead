REM graphics
lcc -Wf-bo1 -c dev/data/tiles/bkg_tileset.c -o bkg_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/pg_idle_tileset.c -o pg_idle_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/abc_tileset.c -o abc_tileset.o
REM maps
lcc -Wf-bo2 -c dev/data/maps/bkg_map.c -o bkg_map.o
lcc -Wf-bo2 -c dev/data/maps/title_map.c -o title_map.o
REM logic
lcc -c dev/utils/char_utils.c -o char_utils.o
lcc -c dev/main.c -o main.o
REM build
lcc -Wl-yt1 -Wl-yo4 -Wl-ya0 -o rom/NuclearHead.gb main.o char_utils.o pg_idle_tileset.o bkg_tileset.o abc_tileset.o bkg_map.o title_map.o
REM clean
del *.o *.lst
pause