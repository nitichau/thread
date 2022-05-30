#include "../include/command.h"
#include "../include/threadpool.h"

void Worker::Threadwork()
{
	while (m_Pool.Running())
	{
		ICommand * job = nullptr;

		if (!m_Pool.GetQueue().empty()) {
			job = m_Pool.GetQueue().front();
			m_Pool.GetQueue().pop();
		}

		if (job)
			job->Execute();
	}
}

