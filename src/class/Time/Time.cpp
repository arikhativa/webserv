
#include <Time/Time.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Time::Time()
	: _hours(0)
	, _minutes(0)
	, _seconds(0)
{
}

Time::~Time()
{
}

Time::Time(const Time &src)
	: _hours(src._hours)
	, _minutes(src._minutes)
	, _seconds(src._seconds)
{
}

bool Time::hasSecondsPassed(int s) const
{
	Time now;

	now.setToNow();
	int total_now_seconds = (now._hours * 3600) + (now._minutes * 60) + now._seconds;
	int total_seconds = (_hours * 3600) + (_minutes * 60) + _seconds;

	return (total_now_seconds - total_seconds) > s;
}

bool Time::isOn(void) const
{
	return _hours || _minutes || _seconds;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Time &Time::operator=(const Time &rhs)
{
	if (this == &rhs)
		return *this;

	_hours = rhs._hours;
	_minutes = rhs._minutes;
	_seconds = rhs._seconds;

	return *this;
}

std::ostream &operator<<(std::ostream &os, const Time &time)
{
	os << std::setfill('0') << std::setw(2) << time.getHours() << ":" << std::setfill('0') << std::setw(2)
	   << time.getMinutes() << ":" << std::setfill('0') << std::setw(2) << time.getSeconds();
	return os;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

void Time::setToNow(void)
{
	time_t currentTime = time(NULL);
	struct tm *timeInfo = localtime(&currentTime);

	_hours = timeInfo->tm_hour;
	_minutes = timeInfo->tm_min;
	_seconds = timeInfo->tm_sec;
}

void Time::set(int h, int m, int s)
{
	_hours = h;
	_minutes = m;
	_seconds = s;
}

int Time::getHours() const
{
	return _hours;
}

int Time::getMinutes() const
{
	return _minutes;
}

int Time::getSeconds() const
{
	return _seconds;
}

/* ************************************************************************** */
