
#include <ChunkManager/ChunkManager.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ChunkManager::ChunkManager(const std::string &body)
	: _body(body)
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ChunkManager::~ChunkManager()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ChunkManager &ChunkManager::operator=(ChunkManager const &rhs)
{
	if (this != &rhs)
	{
		this->_body = rhs.getBody();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, ChunkManager const &i)
{
	o << "ChunkManager[" << i.getBody() << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void ChunkManager::_setBody(const std::string &body)
{
	this->_body = body;
}

const char *ChunkManager::ChunkManagerException::what() const throw()
{
	return ("Error in chunk size");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string ChunkManager::getBody(void) const
{
	return this->_body;
}

bool ChunkManager::isChunked(const std::string &request)
{
	return (request.find(CHUNKED_HEADER) != std::string::npos);
}

std::string ChunkManager::getUnchunkedBody(const std::string &bodyRequest)
{
	std::string body = "";
	std::size_t pos = 0;
	std::string content = bodyRequest;
	while ((pos = content.find(FIELD_BREAK_HEADER)) != std::string::npos)
	{
		std::string size = content.substr(0, pos);
		size_t size_int = converter::hexStringToSizeT(size);
		if (size_int == 0)
			break;
		content = content.substr(pos + 2);
		body += content.substr(0, size_int);
		if (content.length() < size_int + 2)
			throw ChunkManager::ChunkManagerException();
		if (content.substr(size_int, 2) != FIELD_BREAK_HEADER)
			throw ChunkManager::ChunkManagerException();
		content = content.substr(size_int + 2);
	}
	return (body);
}

/* ************************************************************************** */
