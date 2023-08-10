
#include <Tab/Tab.hpp>
#include <gtest/gtest.h>

TEST(Tab, CreateDestroy)
{
	Tab *obj = new Tab();
	delete obj;
}

TEST(Tab, a)
{
	Tab obj1;

	obj1.add("Content-Length=42");
	obj1.add("Content-Type=text/html");
	obj1.add("Host=localhost:8080");
	obj1.add("Accept-Language=en-US,en;q=0.5");
	obj1.add("Accept-Encoding=gzip, deflate");
	char **tab;
	tab = (char **)calloc(6, sizeof(char *));
	tab[0] = strdup("Content-Length=42");
	tab[1] = strdup("Content-Type=text/html");
	tab[2] = strdup("Host=localhost:8080");
	tab[3] = strdup("Accept-Language=en-US,en;q=0.5");
	tab[4] = strdup("Accept-Encoding=gzip, deflate");
	tab[5] = NULL;

	char **res = obj1.toCTable();
	for (int i = 0; tab[i] != NULL; i++)
	{
		std::string str = tab[i];
		std::string str2 = res[i];
		EXPECT_EQ(str, str2);
	}
	obj1.freeTab(res);
	obj1.freeTab(tab);
}
