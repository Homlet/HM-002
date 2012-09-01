// "Main.cpp"
//

#include "Main.h"



int main(int argc, char* argv[])
{
	int running = GL_TRUE;

	if ( !glfwInit() )
		exit( EXIT_FAILURE );

	std::cout << "GLFW successfully initialised" << std::endl;

	if ( !initializeWindow() )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	
	if ( glewInit() != GLEW_OK )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	
	renderer.initializeRenderer();

	// Main game loop
	while ( running )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		renderer.render();

		// Swap front and back buffers
		glfwSwapBuffers();

		// Check for window close signal
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
		           glfwGetWindowParam( GLFW_OPENED );
	}

	glfwTerminate();

	exit( EXIT_SUCCESS );
}


// --------------------------------------------------------------------------------------------------------------------
//  Function that creates a glfw window as specified by the "WIN_" macros
//  in Main.h, and returns the status
//
int initializeWindow( void )
{
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );

	// Open window (attributes specified as macros)
	int window = glfwOpenWindow(
		WIN_W,
		WIN_H,
		WIN_RED_BITS,
		WIN_BLUE_BITS,
		WIN_GREEN_BITS,
		WIN_ALPHA_BITS,
		WIN_DEPTH_BITS,
		0,
		GLFW_WINDOW
	);

	if ( window )
	{
		std::cout << "Window successfully created" << std::endl;

		glfwSetWindowTitle( WIN_TITLE );
	}

	return window;
}