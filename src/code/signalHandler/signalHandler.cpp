#include <signalHandler/signalHandler.hpp>

void signalHandler::sigHandler(int signal)
{
	if (signal == SIGQUIT || signal == SIGINT)
	{
		std::cout << "Exit with signal" << std::endl;
		Poll::exitLoop();
	}
}

void signalHandler::setup(void)
{
	signal(SIGQUIT, signalHandler::sigHandler);
	signal(SIGINT, signalHandler::sigHandler);
}
