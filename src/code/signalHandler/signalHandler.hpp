
#ifndef SIGNALHANDLER_HPP
#define SIGNALHANDLER_HPP

#include <Poll/Poll.hpp>
#include <csignal>

namespace signalHandler
{
	void sigHandler(int signal);
	void sigPipeHandler(int signal);
	void setup(void);
} // namespace signalHandler

#endif
