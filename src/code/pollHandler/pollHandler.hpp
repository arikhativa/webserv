
#ifndef POLLHANDLER_HPP
#define POLLHANDLER_HPP

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <Poll/Poll.hpp>
#include <converter/converter.hpp>

namespace pollHandler
{
	Poll::ret_stt clientWrite(Poll &p, int fd, int revents, Poll::Param &param);
}

#endif
