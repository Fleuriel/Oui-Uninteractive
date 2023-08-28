#include <iostream>
#include <OpenGLApplication.h>





int main()
{
	std::cout << "Hello World\n";

	// Initialize Graphics Pipeline
	OpenGLInit();
	
	OpenGLUpdate();

	OpenGLCleanup();

	return 0;
}



