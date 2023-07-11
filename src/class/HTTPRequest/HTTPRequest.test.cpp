
#include <HTTPRequest/HTTPRequest.hpp>
#include <gtest/gtest.h>

TEST(HTTPRequest, CreateDestroy)
{
	HTTPRequest *obj = new HTTPRequest(0);
	delete obj;
}

TEST(HTTPRequest, Accessor)
{
}

TEST(HTTPRequest, Canonical)
{
}
