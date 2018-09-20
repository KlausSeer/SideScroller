#pragma once
#include "Task.h"
#include <list>
class TaskList
{
	std::list<Task*> tasks;
public:
	TaskList();
	~TaskList();
	void doTasks(float Time);
	void CheckLive();
	void newTask(Task* nueva);
};

