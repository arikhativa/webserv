
#include <utility>

#ifndef ONOFF_HPP
#define ONOFF_HPP

#ifdef TEST_ON
#define private public
#define protected public
#endif

template <typename T>
class OnOff
{
public:
	OnOff(const T &value, bool isOn)
		: data(value, isOn)
	{
	}

	T getValue() const
	{
		return data.first;
	}

	bool isOn() const
	{
		return data.second;
	}

	void setValue(const T &value)
	{
		data.first = value;
	}

	void setOn(bool isOn)
	{
		data.second = isOn;
	}

private:
	std::pair<T, bool> data;
};

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif
