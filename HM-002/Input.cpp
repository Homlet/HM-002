// "Input.cpp"
//

#include "Base.h"
#include "Input.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Polls GLFW for current mouse position
//
void Input::poll()
{
	_mx_old = _mx;
	_my_old = _my;

	glfwGetMousePos( &_mx, &_my );
	
	_dx = _mx - _mx_old;
	_dy = _my - _my_old;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the mouse position as a glm::vec2
//
void Input::getMousePos( int* mx, int* my )
{
	*mx = _mx;
	*my = _my;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the mouse delta as a glm::vec2
//
void Input::getMouseDelta( int* dx, int* dy )
{
	*dx = _dx;
	*dy = _dy;
}
