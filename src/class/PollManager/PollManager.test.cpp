
#include <PollManager/PollManager.hpp>
#include <gtest/gtest.h>

TEST(PollManager, CreateDestroy)
{
	PollManager *obj = new PollManager();
	delete obj;
}

TEST(PollManager, addFds)
{
	PollManager obj;
	int fd[2];
	pipe(fd);
	obj.addFd(fd[0], POLLIN);
	obj.addFd(fd[1], POLLOUT);
}

TEST(PollManager, removeFds)
{
	PollManager obj;
	int fd[2];
	pipe(fd);
	obj.addFd(fd[0], POLLIN);
	obj.addFd(fd[1], POLLOUT);
	obj.removeFd(fd[0]);

	EXPECT_THROW(obj.removeFd(fd[0]), PollManager::PollManagerException);
}

TEST(PollManager, poll)
{
	PollManager obj;
	int fd[2];
	pipe(fd);
	obj.addFd(fd[0], POLLIN);
	obj.addFd(fd[1], POLLOUT);
	// See if i can write to fd[1] and read from fd[0]
	EXPECT_EQ(obj.isInActivity(fd[1]), 1);
	write(fd[1], "a", 1);
	EXPECT_EQ(obj.isInActivity(fd[1]), 1);

	// See if i can read from fd[0]
	EXPECT_EQ(obj.isInActivity(fd[0]), 1);
	char buf[1];
	read(fd[0], buf, 1);

	// See if i can write to fd[1]
	EXPECT_EQ(obj.isInActivity(fd[1]), 1);
}

TEST(PollManager, externalFile)
{
	PollManager obj;
	int fd = open("res/404.html", O_CREAT | O_RDWR, 0666);

	obj.addFd(fd, POLLIN);
	EXPECT_EQ(obj.isInActivity(fd), false);

	int fd2 = open("res/404.html", O_CREAT | O_RDWR, 0666);
	obj.addFd(fd2, POLLIN);
	EXPECT_EQ(obj.isInActivity(fd2), true);

	close(fd);
	close(fd2);
}