//Nuclear Head
// TFG UOC Videojocs
#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdio.h>

//Functions
void init();
void game();

void main() {
    game();
}

void game() {
    
    init();
    printf("\n GAMEBOY NUCELAR HEAD DEMO\n");
    printf("\n\n\n\n\n");
    printf("\nPress start\n");
    waitpad(J_START);

    while (1) {
        printf("\nFin\n");
    }
}

void init() {
	
	DISPLAY_ON;		// Turn on the display
	NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max
}