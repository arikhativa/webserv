
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <defaultPager/defaultPager.hpp>

// TEST(defaultPager, 404)
// {
// 	const char *txt = "<title>404 Page Not Found</title>";
// 	std::string page(defaultPager::getPage(HTTPStatusCode::NOT_FOUND));
// 	EXPECT_TRUE(page.find(txt) != std::string::npos);
// }

// TEST(defaultPager, badPage501)
// {
// 	const char *txt = "<title>404 Page Not Found</title>";
// 	std::string page(defaultPager::getPage(HTTPStatusCode::NOT_IMPLEMENTED));
// 	EXPECT_FALSE(page.find(txt) != std::string::npos);
// }
