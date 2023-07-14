
#include <ServerManager/ServerManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

/* Server should be initialized using the config file, but we dont have it ready yet */
ServerManager::ServerManager()
{
	this->_virtualServers.push_back(Server(1234));
	this->_virtualServers.push_back(Server(4321));
}

// ServerManager::ServerManager(Config config)
// 	: _value(i)
// {
// }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerManager::~ServerManager()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
