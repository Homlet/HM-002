// "Main.cpp"
//

#include "Base.h"
#include "Input.h"
#include "Buffer.h"
#include "Player.h"
#include "Entity.h"
#include "State.h"
#include "Shader.h"
#include "Matrices.h"
#include "Handler.h"
#include "Main.h"


int main(int argc, char* argv[])
{
	int isRunning = GL_TRUE;

	if ( !glfwInit() )
		exit( EXIT_FAILURE );

	std::cout << "GLFW successfully initialised\n";

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

	std::cout << "GLEW successfully initialised\n\n";

	double delta = 0.0, delta_old = 0.0;
	update::State state;
	update::Input input;
	render::Handler renderhandler;

	glfwSetTime( 0.0 );

	// Main game loop
	while ( isRunning )
	{
		delta_old = delta;
		delta = glfwGetTime() - delta_old;

		// Poll mouse changes
		input.poll();

		// Run game logic for current state
		state.update( delta, &input );

		// Render
		renderhandler.render();

		glfwSwapBuffers();

		// Check for window close signal
		isRunning = !glfwGetKey( GLFW_KEY_ESC ) &&
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
	glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 3 );
	glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
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
		WIN_TYPE
	);

	if ( window )
	{
		std::cout << "Window successfully created\n";

		glfwSetWindowTitle( WIN_TITLE );
	}

	return window;
}
