#include "command_engine.h"


int main(int argc, char* argv[]){
	CommandHandling::CommandEngine cmdEngine{argc, argv};
	cmdEngine.run();
	return 0;
}






