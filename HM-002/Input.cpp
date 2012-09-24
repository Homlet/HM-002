// "Input.cpp"
//

#include "WindowMacros.h"

#include "Base.h"

#include "Input.h"

using namespace update;


// --------------------------------------------------------------------------------------------------------------------
//  Sets all members to zero, hides the mouse cursor. Clears the _keys and _keys_old maps
//
Input::Input( void ) :
	_mx( 0 ), _my( 0 ),
	_mx_old( 0 ), _my_old( 0 ),
	_dx( 0 ), _dy( 0 ),
	_left( GLFW_RELEASE ), _middle( GLFW_RELEASE ), _right( GLFW_RELEASE ),
	_left_old( GLFW_RELEASE ), _middle_old( GLFW_RELEASE ), _right_old( GLFW_RELEASE ),
	_isMouseTrapped( false )
{
	trapMouse();
}


// --------------------------------------------------------------------------------------------------------------------
//  Polls GLFW for current mouse position and button state
//
void Input::poll( void )
{
	// Update mouse position variables
	_mx_old = _mx;
	_my_old = _my;

	glfwGetMousePos( &_mx, &_my );
	
	_dx = _mx - _mx_old;
	_dy = _my - _my_old;

	// Update mouse button variables
	_left_old = _left;
	_middle_old = _middle;
	_right_old = _right;
	
	_left = glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT );
	_middle = glfwGetMouseButton( GLFW_MOUSE_BUTTON_MIDDLE );
	_right = glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT );
}


// --------------------------------------------------------------------------------------------------------------------
//  Hides and traps the mouse
//
void Input::trapMouse( void )
{
	if ( !_isMouseTrapped )
	{
		glfwDisable( GLFW_MOUSE_CURSOR );
		_isMouseTrapped = true;
	} else
		fprintf( stderr, "Mouse already trapped." );
}


// --------------------------------------------------------------------------------------------------------------------
//  Shows and untraps the mouse
//
void Input::untrapMouse( void )
{
	if ( _isMouseTrapped )
	{
		_mx = _mx_old = WIN_W / 2;
		_my = _mx_old = WIN_H / 2;
		_dx = _dy = 0;

		glfwEnable( GLFW_MOUSE_CURSOR );
		_isMouseTrapped = false;
	} else
		fprintf( stderr, "Mouse already untrapped." );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the referenced ints to the current mouse position
//
void Input::getMousePos( int* mx, int* my ) const
{
	*mx = _mx;
	*my = _my;
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the referenced ints to the mouse delta since the last poll
//
void Input::getMouseDelta( int* dx, int* dy ) const
{
	*dx = _dx;
	*dy = _dy;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns the given mouse button - GLFW_PRESS or GLFW_RELEASE (which equals 0)
//  If wasJustPressed == true, returns whether the button was pressed this frame
//
bool Input::getMouseButton( int button, bool wasJustPressed ) const
{
	switch ( button )
	{
	case GLFW_MOUSE_BUTTON_LEFT :
		if ( wasJustPressed )
			return _left == GLFW_PRESS && _left_old == GLFW_RELEASE;
		else
			return _left == GLFW_PRESS;
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE :
		if ( wasJustPressed )
			return _middle == GLFW_PRESS && _middle_old == GLFW_RELEASE;
		else
			return _middle == GLFW_PRESS;
	break;

	case GLFW_MOUSE_BUTTON_RIGHT :
		if ( wasJustPressed )
			return _right == GLFW_PRESS && _right_old == GLFW_RELEASE;
		else
			return _right == GLFW_PRESS;
	break;
	}
	
	return false;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns if the mouse is trapped as a bool
//
bool Input::getMouseTrapped( void ) const
{
	return _isMouseTrapped;
}


// ====================================================================================================================
//  Begin defining static keyboard input system
//
namespace update
{
	namespace keyinput
	{
		std::map<int, int> keys, keys_old;


		// --------------------------------------------------------------------------------------------------------------------
		//  Setup GLFW return  call
		//
		void initializeKeyInput( void )
		{
			// Set key callback function to write all changes to the keys map
			glfwSetKeyCallback( onKeyPress );
		}


		// --------------------------------------------------------------------------------------------------------------------
		//  Polls GLFW for current mouse position
		//
		void updateOldKeybuffer( void )
		{
			// Update keyboard old buffer
			keys_old = keys;
		}


		// --------------------------------------------------------------------------------------------------------------------
		//  Returns if given key is down.
		//  If wasJustPressed == true, returns whether the key was pressed this frame
		//
		bool getKeyDown( int key, bool wasJustPressed )
		{
			if ( wasJustPressed )
				return keys[key] == GLFW_PRESS && keys_old[key] == GLFW_RELEASE;
			else
				return keys[key] == GLFW_PRESS;
		}


		// --------------------------------------------------------------------------------------------------------------------
		//  Runs on keypress, inserts key and action into the _keys map
		//
		void GLFWCALL onKeyPress( int key, int action )
		{
			keys[key] = action;
		}
	}
}
