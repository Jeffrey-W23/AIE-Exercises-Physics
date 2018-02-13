// #include, using, etc
#include <crtdbg.h>
#include "aieProject2D1App.h"

int main() {
	
	// Memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new aieProject2D1App();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}