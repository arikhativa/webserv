
#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <cstdio>
#include <iostream>
#include <string>
#include <sys/stat.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class FileManager
{
  public:
	explicit FileManager(const std::string &path);
	~FileManager();

	FileManager &operator=(const FileManager &rhs);

	const std::string getPath(void) const;
	static bool isFileExists(const std::string &path);
	static bool isDirectory(const std::string &path);
	class FileManagerException : public std::exception
	{
		virtual const char *what() const throw();
	};

  private:
	std::string _path;

	void _setPath(const std::string &path);
};

std::ostream &operator<<(std::ostream &o, const FileManager &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* FILE_MANAGER_HPP */
