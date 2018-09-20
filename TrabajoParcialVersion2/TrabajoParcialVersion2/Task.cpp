#include "Task.h"



Task::Task()
{
}


void Task::DoTask(float delayTime)
{
	if (time > delayTime)
	{
		f();
		time = 0.0;
		enabled = false;
	}
	else
		time += 0.1;
}

bool Task::getEnabled()
{
	return enabled;
}

Task::~Task()
{
}
