#include <iostream>
#include <OpenGLApplication.h>





int main()
{
	std::cout << "Hello World\n";

	// Initialize Graphics Pipeline
	OpenGLApplication::OpenGLInit(1366,768);
	
	OpenGLApplication::OpenGLUpdate();

	OpenGLApplication::OpenGLCleanup();

	return 0;
}



