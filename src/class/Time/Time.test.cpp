
#include <Time/Time.hpp>
#include <gtest/gtest.h>

TEST(Time, CreateDestroy)
{
	Time *obj = new Time();
	delete obj;
}

TEST(Time, setToNow)
{
	Time obj;
	Time tmp;

	obj.setToNow();
	EXPECT_FALSE(obj.hasSecondsPassed(10));
	tmp.set(obj.getHours(), obj.getMinutes(), obj.getSeconds() - 5);
	EXPECT_TRUE(tmp.hasSecondsPassed(1));
}
