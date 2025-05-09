#ifndef TIME_H
#define TIME_H

class Time
{

private:
	int hours;
	int minutes;
	int seconds;

public:
	//constructors
	Time();
	Time(int hours, int minutes, int seconds);

	//destructors
	~Time();

	//accessors
	int getHour();
	int getMinutes();
	int getSeconds();

	//mutators
	void setHour(int hours);
	void setMinutes(int minutes);
	void setSeconds(int seconds);

};
#endif
