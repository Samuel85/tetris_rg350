#include <stdlib.h> 
#include <string.h>
#include "system.h"

int 	zoom = 1;
bool 	fullscreen = false;
bool 	enableJoystick = false;

void commandLineArgs(int argc, char **argv){
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-zoom")) {
			if (++i == argc){
				std::cout << "missing zoom value" << std::endl;
			}
			zoom = atoi(argv[i]);			
      if (zoom < 1){
				std::cout << "invalid zoom value" << std::endl;
			}
		}
		else if (!strcmp(argv[i], "-fullscreen")) {
			fullscreen = true;
		}
		else if (!strcmp(argv[i], "-enablejoystick")) {
			enableJoystick = true;
		}		
	}	
}

int main(int argc, char *argv[]){
		commandLineArgs(argc, argv);
	
    System system;
    system.mainLoop();

	return 0;
}
