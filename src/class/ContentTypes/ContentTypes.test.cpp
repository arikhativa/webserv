
#include <ContentTypes/ContentTypes.hpp>
#include <gtest/gtest.h>

TEST(ContentTypes, CreateDestroy)
{
	ContentTypes *obj = new ContentTypes(".html");
	delete obj;

	ContentTypes obj1(".html");
	ContentTypes obj2 = obj1;

	ContentTypes *obj3 = new ContentTypes(".html");
	ContentTypes obj4 = *obj3;

	delete obj3;
}

TEST(ContentTypes, CorrectType)
{
	ContentTypes obj(".html");
	EXPECT_EQ("text/html", obj.get());

	ContentTypes obj1(".png");
	EXPECT_EQ("image/png", obj1.get());

	ContentTypes obj2(".jar");
	EXPECT_EQ("application/java-archive", obj2.get());

	ContentTypes obj3(".m4v");
	EXPECT_EQ("video/x-m4v", obj3.get());
}

TEST(ContentTypes, Exception)
{
	EXPECT_THROW(ContentTypes obj("something"), ContentTypes::InvalidExtensionException);
	EXPECT_THROW(ContentTypes obj(".ht"), ContentTypes::InvalidExtensionException);
	EXPECT_THROW(ContentTypes obj("."), ContentTypes::InvalidExtensionException);
	EXPECT_THROW(ContentTypes obj(""), ContentTypes::InvalidExtensionException);
	EXPECT_THROW(ContentTypes obj("42"), ContentTypes::InvalidExtensionException);
}