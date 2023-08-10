
#include <Pipe/Pipe.hpp>
#include <gtest/gtest.h>

TEST(Pipe, CreateDestroy)
{
	Pipe *obj = new Pipe();
	delete obj;
}