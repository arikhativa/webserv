
#include <signaler/signaler.hpp>

// TODO let poll() know to exit
void signalHandler(int signum)
{
	if (signum == SIGQUIT || signum == SIGINT || signum == SIGTERM)
	{
		std::cout << "Quitting..." << std::endl;
	}
}

void signaler::setAll(void)
{
	std::signal(SIGTERM, signalHandler);
	std::signal(SIGQUIT, signalHandler);
	std::signal(SIGINT, signalHandler);
}
