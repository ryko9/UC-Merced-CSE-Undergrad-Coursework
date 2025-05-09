#include "Time.h"

//constructors
Time::Time()
{
	setHour(0);
	setMinutes(0);
	setSeconds(0);
}

Time::Time(int hours, int minutes, int seconds)
{
	setHour(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

//destructor
Time::~Time()
{
}

//accessors
int Time::getHour()
{
	return hours;
}

int Time::getMinutes()
{
	return minutes;
}

int Time::getSeconds()
{
	return seconds;
}

//mutators
void Time::setHour(int hours)
{
	this->hours = hours;
}

void Time::setMinutes(int minutes)
{
	this->minutes = minutes;
}

void Time::setSeconds(int seconds)
{
	this->seconds = seconds;
}


