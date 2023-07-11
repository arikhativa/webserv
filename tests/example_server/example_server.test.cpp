
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class Config
{
  public:
	virtual ~Config()
	{
	}
	virtual int getPort(void)
	{
		return 0;
	}
};

class MockIConfig : public Config
{
  public:
	MOCK_METHOD(int, getPort, (), (override));
};

class Server
{
  public:
	Server(Config *config)
		: config(config)
	{
	}
	bool start(void)
	{
		if (config->getPort() == 8080)
			return true;
		return false;
	}

  private:
	Config *config;
};

// TEST(Server, CorrectPort)
// {
// 	MockIConfig *config = new MockIConfig;
// 	EXPECT_CALL(*config, getPort()).Times(testing::AtLeast(1)).WillOnce(testing::Return(8080));

// 	Server server(config);

// 	EXPECT_TRUE(server.start());
// 	delete config;
// }
