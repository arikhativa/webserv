
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class FooChild
{
  public:
	virtual void doThis()
	{
	}
	virtual bool doThat(int n, double x)
	{
		return false;
	}
};

class MockFooChild : public FooChild
{
  public:
	MOCK_METHOD(void, doThis, (), (override));
	MOCK_METHOD(bool, doThat, (int n, double x), (override));
};

TEST(PainterTest, CanDrawSomething)
{
	MockFooChild a
}