#include "Task.h"



Task::Task()
{
}


void Task::DoTask(float delayTime)
{
	if (time > delayTime)
	{
		f();
		time = 0.0f;
		enabled = false;
	}
	else
		time += 0.1f;
}

bool Task::getEnabled()
{
	return enabled;
}

Task::~Task()
{
}
