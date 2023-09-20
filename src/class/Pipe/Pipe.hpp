
#ifndef PIPE_HPP
#define PIPE_HPP

#include <iostream>
#include <string>

#include <unistd.h>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Pipe
{
  public:
	Pipe();
	~Pipe();

	class PipeException : public std::exception
	{
	  public:
		virtual const char *what() const throw();
	};

	void initPipe();

	void setChild(void) const;
	void setParent(void) const;
	void write(const std::string &str) const;
	void closeInput(void) const;
	int getOutput(void) const;
	int getInput(void) const;

  private:
	int _inputPipe[2];
	int _outputPipe[2];

	static const int ERROR;
	static const int INPUT;
	static const int OUTPUT;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* PIPE_HPP */
