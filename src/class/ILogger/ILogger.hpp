
#ifndef I_LOGGER_HPP
#define I_LOGGER_HPP

#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class ILogger
{
  public:
	static void	consoleLogDebug(const std::string& message) 
	{
		std::cout << "\033[1;34m" << "[DEBUG] \033[1;33m" << message << "\033[0m" << std::endl;
	}
	static void	consoleLogError(const std::string& message) 
	{
		std::cout << "\033[1;31m" << "[ERROR] \033[1;31m" << message << "\033[0m" << std::endl;
	}
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* I_LOGGER_HPP */
