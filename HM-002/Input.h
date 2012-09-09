// "Input.h"
//

#pragma once

#include <map>

// ----------------------------------------------------------------------------
//  DECLARATIONS
// ----------------------------------------------------------------------------

namespace update
{
	class Input {
	private:
		int _mx, _my;
		int _mx_old, _my_old;
		int _dx, _dy;
		int _left, _middle, _right;
		int _left_old, _middle_old, _right_old;
		bool _isMouseTrapped;
	public:
		Input( void );

		void poll( void );

		void   trapMouse( void );
		void untrapMouse( void );
		
		void getMousePos( int* mx, int* my ) const;
		void getMouseDelta( int* dx, int* dy ) const;
		bool getMouseButton( int button, bool wasJustPressed = false ) const;
		bool getMouseTrapped( void ) const;
	};

	namespace keyinput
	{
		void initializeKeyInput( void );
		void updateOldKeybuffer( void );

		bool getKeyDown( int key, bool wasJustPressed = false );

		void GLFWCALL onKeyPress( int key, int action );
	}
}
