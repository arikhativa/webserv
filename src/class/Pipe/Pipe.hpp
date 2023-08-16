
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

	void setChild(void);
	void setParent(void);
	void write(const std::string &str);
	void closeInput(void);
	int getOutput(void) const;
	int getInput(void) const;

  private:
	int _inputPipe[2];
	int _outputPipe[2];
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* PIPE_HPP */
