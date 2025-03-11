#include <Application.h>

class Game : public Application
{
	void run() override
	{
		while (true)
		{

		}
	}
};

Application* create_application()
{
	return new Game();
}