#include <App/IMCApplication.h>

#include "IMCPrerequisites.h"

int main()
{
	try
	{
		IMCApplication app;
		app.OnCreate();
	}
	catch (const std::exception& e)
	{
		std::clog << e.what() << std::endl;
	}
}