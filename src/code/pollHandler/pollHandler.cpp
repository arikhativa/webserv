
#include <pollHandler/pollHandler.hpp>

Poll::ret_stt pollHandler::clientWrite(Poll &p, int fd, int revents, Poll::Param &param)
{
	(void)p;
	(void)fd;
	if (!Poll::isWriteEvent(revents))
		return Poll::CONTINUE;
	try
	{
		param.call.sendResponse();

		BasicHTTPRequest::Type t = param.call.getBasicRequest().getType();

		std::cout << "[" << fd << "] <-- " << BasicHTTPRequest::toStringType(t) << " "
				  << param.call.getBasicRequest().getPath() << " "
				  << converter::HTTPResponseSimplified(param.call.getResponse()) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return Poll::DONE_CLOSE_FD;
	}

	if (param.call.getBytesSent() < param.call.getResponse().size())
		return Poll::CONTINUE;
	param.call.terminate();
	return Poll::DONE_CLOSE_FD;
}
