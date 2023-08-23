
#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <cstdio>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>

#include <converter/converter.hpp>

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
	static std::string getFileDate(const std::string &path);
	static std::string getFileContent(const std::string &path);
	static std::string getDirectoryPreview(const std::string &path, std::string relative_path);
	static size_t getFileSize(const std::string &path);
	static bool isFileExists(const std::string &path);
	static bool isDirectory(const std::string &path);
	static bool isOpen(const std::fstream &fs);
	class FileManagerException : public std::exception
	{
		virtual const char *what() const throw();
	};

  private:
	std::string _path;
	static std::string _setUrlForHyperlinks(const std::string &url);
	static std::string _setHyperlinks(const std::string &path, std::string relative_path, std::string name);
	void _setPath(const std::string &path);
	static const std::string PREVIOUS_DIR;
	static const std::string ACTUAL_DIR;
};

std::ostream &operator<<(std::ostream &o, const FileManager &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* FILE_MANAGER_HPP */
