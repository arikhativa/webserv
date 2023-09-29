
#include <FileManager/FileManager.hpp>

const std::string FileManager::PREVIOUS_DIR("/..");
const std::string FileManager::ACTUAL_DIR("/.");

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

bool FileManager::isOpen(const std::fstream &fs)
{
	if (!fs.is_open() || fs.bad() || fs.fail())
		return false;
	return true;
}

void FileManager::_setPath(const std::string &path)
{
	this->_path = path;
}

const char *FileManager::FileManagerException::what() const throw()
{
	return ("Error when accessing the path");
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
		if (path.empty() || path == "")
			throw FileManager::FileManagerException();
		struct stat statbuf;
		if (stat(path.c_str(), &statbuf) == 0)
			return (!isDirectory(path));
		return (false);
	}
	catch (const std::exception &e)
	{
		throw FileManager::FileManagerException();
	}
}
bool FileManager::isDirectory(const std::string &path)
{
	try
	{
		if (path.empty() || path == "")
			throw FileManager::FileManagerException();
		struct stat statbuf;
		if (stat(path.c_str(), &statbuf) == 0)
			return (S_ISDIR(statbuf.st_mode));
		return (false);
	}
	catch (const std::exception &e)
	{
		throw FileManager::FileManagerException();
	}
}

void FileManager::createFile(const BasicHTTPRequest &request, const std::string &root)
{
	std::string path(root + request.getPath());
	std::ofstream file(path.c_str(), std::ios::binary);

	if (!file.is_open())
		throw FileManager::FileManagerException();

	file.write(&(request.getBody()[0]), request.getBody().size());
	file.close();
}

std::string FileManager::getFileDate(const std::string &path)
{
	char buf[32];
	struct tm *tm;

	struct stat statbuf;
	if (stat(path.c_str(), &statbuf) == -1)
		throw FileManager::FileManagerException();
	tm = gmtime(&statbuf.st_mtime);
	int ret = strftime(buf, 32, "%d-%b-%Y %H:%M", tm);
	return (std::string(buf, ret));
}

// std::vector< char > FileManager::getFileContent(const std::string &path)
// {
// 	std::ifstream file(path.c_str(), std::ios::binary);
// 	if (!file.is_open())
// 		throw FileManager::FileManagerException();

// 	file.seekg(0, std::ios::end);
// 	std::streampos fileSize = file.tellg();
// 	file.seekg(0, std::ios::beg);

// 	std::vector< char > content(fileSize);

// 	file.read(&content[0], fileSize);

// 	file.close();

// 	return content;
// }

std::string FileManager::getFileContent(const std::string &path)
{
	std::string content = "";
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw FileManager::FileManagerException();
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	content = buffer.str();
	return (content);
}

size_t FileManager::getFileSize(const std::string &path)
{
	struct stat statbuf;
	if (stat(path.c_str(), &statbuf) == -1)
		throw FileManager::FileManagerException();
	return (statbuf.st_size);
}

std::string FileManager::_setUrlForHyperlinks(const std::string &url)
{
	std::string result = url;
	while (result.size() >= PREVIOUS_DIR.length() && result.substr(result.length() - 3) == PREVIOUS_DIR)
	{
		size_t pos = result.find_last_of(PREVIOUS_DIR);
		if (pos != std::string::npos)
		{
			std::string url_tmp = result.substr(0, pos - 2);
			size_t pos2 = url_tmp.find_last_of("/");
			if (pos2 != std::string::npos)
				result = url_tmp.substr(0, pos2 + 1) + result.substr(pos + 1);
			else
				result = result.substr(pos + 1);
		}
	}
	if (result.size() >= ACTUAL_DIR.length() && result.substr(result.length() - 2) == ACTUAL_DIR)
		result = result.substr(0, result.length() - 2);
	return (result);
}

std::string FileManager::_setHyperlinks(const std::string &path, std::string relative_path, std::string name)
{
	std::ostringstream content;
	std::string url = _setUrlForHyperlinks(relative_path + name);
	if (name.length() > 50)
		name = name.substr(0, 47) + "..>";
	content << "<a href=\"" + url + "\">" + name + "</a>";
	content << std::setw(68 - name.length()) << FileManager::getFileDate(path);
	return (content.str());
}

std::string FileManager::getDirectoryPreview(const std::string &path, std::string relativePath)
{
	std::ostringstream content;
	content << "<!DOCTYPE html><html>\r\n<head><title>Index of " + relativePath + "</title></head>\r\n";
	content << "<body>\r\n<h1>Index of " + relativePath + "</h1><hr><pre>\n";
	DIR *dir;
	struct dirent *ent;
	if (!relativePath.empty() && relativePath[0] != '/' && path[path.length() - 1] != '/')
		relativePath = "/" + relativePath;
	if (!relativePath.empty() && relativePath[relativePath.length() - 1] != '/')
		relativePath += "/";
	if (!isDirectory(path + relativePath))
		throw FileManager::FileManagerException();
	if ((dir = opendir((path + relativePath).c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			std::string path_aux(path + relativePath + ent->d_name);
			if (ent->d_name[0] == '.' && ent->d_name[1] == '\0')
				continue;
			content << _setHyperlinks(path_aux, relativePath, ent->d_name);
			if (isDirectory(path_aux))
				content << std::setw(20) << "-";
			else
				content << std::setw(20) << converter::numToString(FileManager::getFileSize(path_aux));
			content << "<br>";
		}
		closedir(dir);
	}
	content << "</body>\n</html>";
	return (content.str());
}

/* ************************************************************************** */
