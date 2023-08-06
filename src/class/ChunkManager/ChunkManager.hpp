
#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP

#include <iostream>
#include <string>

#include <converter/converter.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

const std::string CHUNKED_HEADER = "Transfer-Encoding: chunked";
static const std::string FIELD_BREAK_HEADER = "\r\n";

class ChunkManager
{
  public:
	explicit ChunkManager(const std::string &body);
	~ChunkManager();

	ChunkManager &operator=(const ChunkManager &rhs);

	static bool isChunked(const std::string &body);
	static std::string getUnchunkedBody(const std::string &bodyRequest);
	const std::string getBody(void) const;

	class ChunkManagerException : public std::exception
	{
		virtual const char *what() const throw();
	};

  private:
	std::string _body;

	void _setBody(const std::string &body);
};

std::ostream &operator<<(std::ostream &o, const ChunkManager &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* CHUNK_MANAGER_HPP */
