
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

class Painter
{
  public:
	Painter(FooChild *fooChild)
		: fooChild(fooChild)
	{
	}
	bool DrawCircle(void)
	{
		fooChild->doThis();
		if (fooChild->doThat(1, 2.2))
			return true;
		return false;
	}

  private:
	FooChild *fooChild;
};

using ::testing::AtLeast; // #1

TEST(PainterTest, CanDrawSomething)
{
	MockFooChild turtle;				// #2
	EXPECT_CALL(turtle, doThis())		// #3
		.Times(AtLeast(1));
	EXPECT_CALL(turtle, doThat(1, 2.2)) // #3
		.Times(AtLeast(1))
		.WillOnce(testing::Return(false));

	Painter painter(&turtle);		   // #4

	EXPECT_TRUE(painter.DrawCircle()); // #5
}