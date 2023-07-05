
#include <ConfFile/ConfFile.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ConfFile::ConfFile(const std::string &file)
	: _fileName(file)
{
	std::fstream fs;

	fs.open(file.c_str(), std::fstream::in);
	if (!fs.is_open() || fs.bad())
		throw std::runtime_error("Can't open file: " + file);

	std::list<Token *> tokens(lexer::tokenize(fs));
	fs.close();
}

ConfFile::ConfFile(const ConfFile &src)
{
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ConfFile::~ConfFile()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ConfFile &ConfFile::operator=(ConfFile const &rhs)
{
	(void)rhs;
	return *this;
}

std::ostream &operator<<(std::ostream &o, ConfFile const &i)
{
	o << "ConfFile[" << i.getFileName() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string ConfFile::getFileName(void) const
{
	return this->_fileName;
}

std::list<IServerConf *> ConfFile::getServers(void) const
{
	return this->_servers;
}

/* ************************************************************************** */
