
#ifndef POLLHANDLER_HPP
#define POLLHANDLER_HPP

#include <fstream>

#include <HTTPResponse/HTTPResponse.hpp>
#include <Poll/Poll.hpp>
#include <converter/converter.hpp>

namespace pollHandler
{

	Poll::ret_stt writeClient(Poll &p, int fd, int revents, Poll::Param param);
	Poll::ret_stt readClient(Poll &p, int fd, int revents, Poll::Param param);
	Poll::ret_stt newClient(Poll &p, int fd, int revents, Poll::Param param);
} // namespace pollHandler

#endif