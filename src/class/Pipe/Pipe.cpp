
#include <Pipe/Pipe.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

const int Pipe::ERROR(0);
const int Pipe::INPUT(0);
const int Pipe::OUTPUT(1);

Pipe::Pipe()
{
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

void Pipe::initPipe()
{
	if (pipe(_inputPipe) < ERROR || pipe(_outputPipe) < ERROR)
		throw Pipe::PipeException();
	std::cout << "New pipe -->\t[" << _inputPipe[OUTPUT] << "]" << std::endl;
	std::cout << "New pipe <--\t[" << _outputPipe[INPUT] << "]" << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Pipe::setChild(void) const
{
	dup2(_inputPipe[INPUT], STDIN_FILENO);
	dup2(_outputPipe[OUTPUT], STDOUT_FILENO);
	close(_inputPipe[INPUT]);
	close(_inputPipe[OUTPUT]);
	close(_outputPipe[INPUT]);
	close(_outputPipe[OUTPUT]);
}

void Pipe::setParent(void) const
{
	close(_inputPipe[INPUT]);
	close(_outputPipe[OUTPUT]);
}

void Pipe::write(const std::string &str) const
{
	::write(_inputPipe[OUTPUT], str.c_str(), str.length());
}

void Pipe::closeInput(void) const
{
	close(_inputPipe[OUTPUT]);
}

int Pipe::getOutput(void) const
{
	return (_outputPipe[INPUT]);
}

int Pipe::getInput(void) const
{
	return (_inputPipe[OUTPUT]);
}

/* ************************************************************************** */
