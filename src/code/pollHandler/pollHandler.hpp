
#ifndef POLLHANDLER_HPP
#define POLLHANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Poll/Poll.hpp>

namespace pollHandler
{

	Poll::ret_stt writeClient(Poll &p, int fd, int revents, void *call);
	Poll::ret_stt readClient(Poll &p, int fd, int revents, void *call);
	Poll::ret_stt readFile(Poll &p, int fd, int revents, void *call);
	Poll::ret_stt newClient(Poll &p, int fd, int revents, void *call);
} // namespace pollHandler

#endif