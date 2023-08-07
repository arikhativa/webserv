
#include <FileManager/FileManager.hpp>
#include <gtest/gtest.h>

TEST(FileManager, CreateDestroy)
{

	FileManager *obj = new FileManager("res/");
	delete obj;
}

TEST(FileManager, Accessor)
{
	std::string val = "res/";
	FileManager obj(val);

	EXPECT_EQ(val, obj.getPath());
}

TEST(FileManager, Canonical)
{
	FileManager obj1("res/");
	FileManager obj2("res/");
	FileManager obj3(obj1);

	EXPECT_EQ(obj1.getPath(), obj3.getPath());
	obj2 = obj1;
	EXPECT_EQ(obj1.getPath(), obj2.getPath());
}

TEST(FileManager, directory)
{
	EXPECT_EQ(true, FileManager::isDirectory("res"));
	EXPECT_EQ(true, FileManager::isDirectory("res/"));
	EXPECT_EQ(true, FileManager::isDirectory("res/./"));
	EXPECT_EQ(true, FileManager::isDirectory("res/././"));
	EXPECT_EQ(true, FileManager::isDirectory("res/../res"));
	EXPECT_EQ(true, FileManager::isDirectory("res/../res/"));
	EXPECT_EQ(true, FileManager::isDirectory("res/../res/./"));

	EXPECT_EQ(false, FileManager::isDirectory("/res"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/./"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/././"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/../res"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/../res/"));
	EXPECT_EQ(false, FileManager::isDirectory("/res/../res/./"));
	EXPECT_EQ(false, FileManager::isDirectory("other"));
	EXPECT_EQ(false, FileManager::isDirectory("res/404.html"));

	FileManager obj("res/");
	EXPECT_EQ(true, FileManager::isDirectory(obj.getPath()));
	EXPECT_EQ(true, obj.isDirectory(obj.getPath()));
	EXPECT_EQ(true, obj.isDirectory(obj.getPath() + "/"));
}

TEST(FileManager, file)
{
	EXPECT_EQ(true, FileManager::isFileExists("res/404.html"));
	EXPECT_EQ(true, FileManager::isFileExists("res/./404.html"));
	EXPECT_EQ(true, FileManager::isFileExists("res/../res/404.html"));
	EXPECT_EQ(true, FileManager::isFileExists("res/../res/./404.html"));

	EXPECT_EQ(false, FileManager::isFileExists("res"));
	EXPECT_EQ(false, FileManager::isFileExists("res/"));
	EXPECT_EQ(false, FileManager::isFileExists("res/./"));
	EXPECT_EQ(false, FileManager::isFileExists("res/././"));
	EXPECT_EQ(false, FileManager::isFileExists("res/../res"));
	EXPECT_EQ(false, FileManager::isFileExists("res/../res/"));
	EXPECT_EQ(false, FileManager::isFileExists("res/../res/./"));
	EXPECT_EQ(false, FileManager::isFileExists("other"));
	EXPECT_EQ(false, FileManager::isFileExists("/res"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/./"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/././"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/../res"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/../res/"));
	EXPECT_EQ(false, FileManager::isFileExists("/res/../res/./"));
	EXPECT_EQ(false, FileManager::isFileExists("other"));

	FileManager obj("res/");
	EXPECT_EQ(true, FileManager::isFileExists(obj.getPath() + "/404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/./404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/./404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/../res/404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/../res/./404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/../res/../res/404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/../res/../res/./404.html"));
	EXPECT_EQ(true, obj.isFileExists(obj.getPath() + "/../res/../res/../res/../res/404.html"));
}

TEST(FileManager, exceptions)
{
	EXPECT_THROW(FileManager::isDirectory(""), FileManager::FileManagerException);
	EXPECT_THROW(FileManager::isFileExists(""), FileManager::FileManagerException);
}

TEST(FileManager, fileContent)
{
	std::string url = "res/404.html";
	std::string content = "<div id=\"main\">\n\t<div class=\"fof\">\n\t\t\t<h1>Error 404</h1>\n\t</div>\n</div>";
	FileManager obj(url);

	EXPECT_EQ(content, obj.getFileContent(url));

	EXPECT_THROW(obj.getFileContent(""), FileManager::FileManagerException);
	EXPECT_THROW(obj.getFileContent("other"), FileManager::FileManagerException);
}

TEST(FileManager, getFileDate)
{
	std::string url = "res/404.html";
	FileManager obj(url);

	EXPECT_THROW(obj.getFileDate(""), FileManager::FileManagerException);
	EXPECT_THROW(obj.getFileDate("other"), FileManager::FileManagerException);
}

TEST(FileManager, getFileSize)
{
	std::string url = "res/404.html";
	FileManager obj(url);

	EXPECT_EQ(71, obj.getFileSize(url));

	EXPECT_THROW(obj.getFileSize(""), FileManager::FileManagerException);
	EXPECT_THROW(obj.getFileSize("other"), FileManager::FileManagerException);
}

TEST(FileManager, getDirectoryPreview)
{
	std::string path = "res/";
	std::string relativePath = "preview";
	std::string directoryStart =
		"<!DOCTYPE html><html>\r\n"
		"<head><title>Index of preview</title></head>\r\n"
		"<body>\r\n"
		"<h1>Index of preview</h1><hr><pre>\n"
		"<a href=\"preview/400.html\">400.html</a>                                           ";
	std::string directoryEnd = "                   "
							   "-<br>"
							   "</body>\n"
							   "</html>";

	std::string result = FileManager::getDirectoryPreview(path, relativePath);
	EXPECT_EQ(directoryStart, result.substr(0, directoryStart.length()));
	EXPECT_EQ(directoryEnd, result.substr(result.length() - directoryEnd.length()));

	EXPECT_THROW(FileManager::getDirectoryPreview("", ""), FileManager::FileManagerException);
	EXPECT_THROW(FileManager::getDirectoryPreview("some", "some"), FileManager::FileManagerException);
}