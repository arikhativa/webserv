
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <string>

class Obj
{
  public:
	Obj()
	{
		_list.emplace_back("hello");
		_list.emplace_back("there");
	}
	const std::list<std::string> &getList(void) const
	{
		return _list;
	}

  private:
	std::list<std::string> _list;
};

TEST(list, ReturnConstRef)
{
	Obj obj;
	const std::list<std::string> &list = obj.getList();
	std::list<std::string>::const_iterator it = list.begin();

	EXPECT_EQ(*it, "hello");
	EXPECT_EQ(*(++it), "there");
	EXPECT_EQ(list.front(), "hello");
	EXPECT_EQ(list.back(), "there");
}
