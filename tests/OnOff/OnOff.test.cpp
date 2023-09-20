#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <OnOff/OnOff.hpp>

TEST(OnOff, SimpleTest)
{
	int i = 5;

	OnOff< int > obj(i, false);

	EXPECT_EQ(5, obj.getValue());
	EXPECT_EQ(false, obj.isOn());
	obj.setOn(true);
	EXPECT_EQ(true, obj.isOn());
}
