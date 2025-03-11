#include "Application.h"

//////////////////////////////
/// To be defined by the user
//////////////////////////////
extern Application* create_application();

int main(int argc, char** argv)
{
	auto program = create_application();
	program->run();
	delete program;

	return 0;
}