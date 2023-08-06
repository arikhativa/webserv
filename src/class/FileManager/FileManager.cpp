
#include <FileManager/FileManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FileManager::FileManager(const std::string &path)
	: _path(path)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FileManager::~FileManager()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FileManager &FileManager::operator=(FileManager const &rhs)
{
	if (this != &rhs)
	{
		this->_path = rhs.getPath();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, FileManager const &i)
{
	o << "FileManager[" << i.getPath() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void FileManager::_setPath(const std::string &path)
{
	this->_path = path;
}

const char *FileManager::FileManagerException::what() const throw()
{
	return ("Error when accessing the path");
}

const char *FileManager::UndefinedFilePathException::what() const throw()
{
	return ("Undefined file path");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string FileManager::getPath(void) const
{
	return this->_path;
}

bool FileManager::isFileExists(const std::string &path)
{
	try
	{
		if (path.empty())
			throw FileManager::UndefinedFilePathException();
		struct stat statbuf;
		if (stat(path.c_str(), &statbuf) == 0)
			return (!isDirectory(path));
		return (false);
	}
	catch (const std::exception &e)
	{
		throw FileManager::FileManagerException();
		return (false);
	}
}

bool FileManager::isDirectory(const std::string &path)
{
	try
	{
		if (path.empty())
			throw FileManager::UndefinedFilePathException();
		struct stat statbuf;
		stat(path.c_str(), &statbuf);
		return (S_ISDIR(statbuf.st_mode));
	}
	catch (const std::exception &e)
	{
		throw FileManager::FileManagerException();
		return (false);
	}
}

/* ************************************************************************** */
