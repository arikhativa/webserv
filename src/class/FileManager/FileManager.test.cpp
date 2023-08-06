
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