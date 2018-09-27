#include "TaskList.h"


TaskList::TaskList()
{
}


TaskList::~TaskList()
{
}

void TaskList::doTasks(float Time)
{
	for each (Task* var in tasks)
	{
		var->DoTask(Time);
	}
}

void TaskList::CheckLive()
{
	std::list<Task*>::iterator i = tasks.begin();
	while (i != tasks.end())
	{
		if (!(*i)->getEnabled())
		{
			tasks.erase(i++);
		}
		else
			++i;
	}
}

void TaskList::newTask(Task * nueva)
{
	tasks.push_back(nueva);
}

void TaskList::Clear()
{
	tasks.clear();
}
