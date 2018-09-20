#pragma once
#include <functional>
class Task
{
	float time = 0.0;
	void(*f)();
	bool enabled = true;
public:
	Task();
	Task(void(*pf)()) : f(pf) {};
	void DoTask(float delayTime);
	bool getEnabled();
	~Task();
};

