REM graphics
lcc -Wf-bo1 -c dev/data/tiles/bkg_tileset.c -o bkg_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/gui_tileset.c -o gui_tileset.o
REM maps
lcc -Wf-bo2 -c dev/data/maps/bkg_map.c -o bkg_map.o
lcc -Wf-bo2 -c dev/data/maps/gui_map.c -o gui_map.o
REM logic
lcc -c dev/main.c -o main.o
REM build
lcc -Wl-yt1 -Wl-yo4 -Wl-ya0 -o rom/NuclearHead.gb main.o bkg_tileset.o gui_tileset.o bkg_map.o gui_map.o
REM clean
del *.o *.lst
pause