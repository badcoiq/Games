#include "badcoiq.h"
#include "Games.h"

int main(int argc, char* argv[])
{
	Games app;
	if (app.Init())
	{
		app.Run();
	}

	return EXIT_SUCCESS;
}

Games::Games()
{
}

Games::~Games()
{
}

bool Games::Init()
{
	return true;
}

void Games::Run()
{
}

