
#include <ChunkManager/ChunkManager.hpp>
#include <gtest/gtest.h>

TEST(ChunkManager, CreateDestroy)
{
	ChunkManager *obj = new ChunkManager("7\r\nMozilla\r\n");
	delete obj;
}

TEST(ChunkManager, Accessor)
{
	std::string val = "7\r\nMozilla\r\n";
	ChunkManager obj(val);

	EXPECT_EQ(val, obj.getBody());
}

TEST(ChunkManager, Canonical)
{
	std::string val = "7\r\nMozilla\r\n";
	std::string val2 = "7\r\nMozilla\r\n";
	ChunkManager obj1(val);
	ChunkManager obj2(val2);
	ChunkManager obj3(obj1);

	EXPECT_EQ(obj1.getBody(), obj3.getBody());
	obj2 = obj1;
	EXPECT_EQ(obj1.getBody(), obj2.getBody());
}

TEST(ChunkManager, isChunked)
{
	std::string request = "GET / HTTP/1.1\r\nHost: www.w3.org\r\nTransfer-Encoding: chunked\r\n\r\n7\r\nMozilla\r\n";
	EXPECT_EQ(true, ChunkManager::isChunked(request));

	std::string val = "7\r\nMozilla\r\n0\r\n\r\n";
	EXPECT_EQ(false, ChunkManager::isChunked(val));
}

TEST(ChunkManager, getUnchunkedBody)
{
	std::string val = "7\r\nMozilla\r\n";

	EXPECT_EQ("Mozilla", ChunkManager::getUnchunkedBody(val));

	std::string val3 = "7\r\nMozilla\r\n";
	EXPECT_EQ("Mozilla", ChunkManager::getUnchunkedBody(val3));

	std::string val5 = "11\r\nde cadena chunked\r\n";
	EXPECT_EQ("de cadena chunked", ChunkManager::getUnchunkedBody(val5));

	std::string val4 = "12\r\nEsta es una prueba\r\n11\r\nde cadena chunked\r\n";
	EXPECT_EQ("Esta es una pruebade cadena chunked", ChunkManager::getUnchunkedBody(val4));
}

TEST(ChunkManager, exception)
{
	std::string val = "7\r\nMozilla\r\n17\r\nDeveloper Network\r\n0\r\n\r\n";
	EXPECT_THROW(ChunkManager::getUnchunkedBody(val), ChunkManager::ChunkManagerException);

	std::string val2 = "7\r\nMola\n\r\n";
	EXPECT_THROW(ChunkManager::getUnchunkedBody(val2), ChunkManager::ChunkManagerException);
}