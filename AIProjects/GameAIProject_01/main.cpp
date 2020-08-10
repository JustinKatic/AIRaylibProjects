
#include "Application.h"
#include <iostream>
#include<time.h>


int main(int argc, char* argv[])
{
    srand(time(NULL));
	{      
		Application app;		
		SetTargetFPS(60);
		app.Run();
	}

	return 0;
}
