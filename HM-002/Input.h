// "Input.h"
//

#pragma once


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
	public:
		void poll();
		
		void getMousePos( int* mx, int* my );
		void getMouseDelta( int* dx, int* dy );
	};
}