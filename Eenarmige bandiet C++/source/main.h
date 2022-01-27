#ifndef _H_AGK_TEMPLATE_
#define _H_AGK_TEMPLATE_

// Link to GDK libraries
#include "AGK.h"

#define DEVICE_WIDTH 1280
#define DEVICE_HEIGHT 720
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false

// Uniek
#define COMPANY_NAME "Dennis"

// Global values
class app
{
	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// Main functies
		void Begin( void );
		int Loop( void );
		void End( void );
};

extern app App;

#endif

// Loadimage function
#ifdef LoadImage
 #undef LoadImage
#endif