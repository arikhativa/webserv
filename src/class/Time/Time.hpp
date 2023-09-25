
#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class Time
{
  public:
	Time();
	~Time();
	Time(const Time &src);

	Time &operator=(const Time &rhs);

	void setToNow(void);
	void set(int h, int m, int s);
	int getHours(void) const;
	int getMinutes(void) const;
	int getSeconds(void) const;
	bool hasSecondsPassed(int s) const;
	bool isOn(void) const;

  private:
	int _hours;
	int _minutes;
	int _seconds;
};

std::ostream &operator<<(std::ostream &o, const Time &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* TIME_HPP */
