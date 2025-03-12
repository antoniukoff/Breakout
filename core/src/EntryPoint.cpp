#include "Application.h"

//////////////////////////////
/// To be defined by the user
//////////////////////////////
extern std::unique_ptr<Application> create_application();

int main(int argc, char** argv)
{
	auto program = create_application();
	program->run();

	return 0;
}