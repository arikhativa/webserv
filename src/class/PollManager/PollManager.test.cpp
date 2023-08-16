
#include <PollManager/PollManager.hpp>
#include <gtest/gtest.h>

TEST(PollManager, CreateDestroy)
{
	PollManager *obj = new PollManager();
	delete obj;
}

TEST(PollManager, fdsNotAvailable)
{
	PollManager obj;
	int fd[2];
	int someRandomFd = 1234;
	int someRandomFd2 = 5678;
	fd[0] = someRandomFd;
	fd[1] = someRandomFd2;

	EXPECT_EQ(obj.isAvailable(fd[0], POLLOUT), false);
	EXPECT_EQ(obj.isAvailable(fd[1], POLLOUT), false);
	EXPECT_EQ(obj.isAvailable(fd[0], POLLIN), false);
	EXPECT_EQ(obj.isAvailable(fd[1], POLLIN), false);
}

TEST(PollManager, poll)
{
	PollManager obj;
	int fd[2];

	pipe(fd);

	EXPECT_EQ(obj.isAvailable(fd[1], POLLOUT), true);
	write(fd[1], "a", 1);
	EXPECT_EQ(obj.isAvailable(fd[1], POLLOUT), true);

	EXPECT_EQ(obj.isAvailable(fd[0], POLLIN), true);

	char buf[2];
	read(fd[0], buf, 1);
	buf[1] = '\0';
	std::string res = buf;

	EXPECT_EQ(res, "a");
	EXPECT_EQ(obj.isAvailable(fd[1], POLLOUT), true);
}

TEST(PollManager, dupFd)
{
	PollManager obj;
	int fd = open("res/cgi/simple.php", O_CREAT | O_RDWR, 0666);

	EXPECT_EQ(obj.isAvailable(fd, POLLIN), true);
	EXPECT_EQ(obj.isAvailable(fd, POLLOUT), true);

	int fd2 = dup(fd);
	EXPECT_EQ(obj.isAvailable(fd2, POLLIN), true);

	close(fd);
	close(fd2);
}
