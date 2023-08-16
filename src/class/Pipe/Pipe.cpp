
#include <Pipe/Pipe.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Pipe::Pipe()
{
	if (pipe(_inputPipe) < 0 || pipe(_outputPipe) < 0)
		throw Pipe::PipeException();
}

const char *Pipe::PipeException::what() const throw()
{
	return "Error in Pipe";
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Pipe::~Pipe()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

void Pipe::setChild(void)
{
	dup2(_inputPipe[0], STDIN_FILENO);
	dup2(_outputPipe[1], STDOUT_FILENO);
	close(_inputPipe[0]);
	close(_inputPipe[1]);
	close(_outputPipe[0]);
	close(_outputPipe[1]);
}

void Pipe::setParent(void)
{
	close(_inputPipe[0]);
	close(_outputPipe[1]);
}

void Pipe::write(const std::string &str)
{
	::write(_inputPipe[1], str.c_str(), str.length());
}

void Pipe::closeInput(void)
{
	close(_inputPipe[1]);
}

int Pipe::getOutput(void) const
{
	return (_outputPipe[0]);
}

int Pipe::getInput(void) const
{
	return (_inputPipe[1]);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
