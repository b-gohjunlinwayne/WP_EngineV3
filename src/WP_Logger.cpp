#include <WP_Logger.h>
#include <iostream>

WP_LogManager& WP_LogManager::GetInstance()
{
	static WP_LogManager instance;
	return instance;
}

void WP_LogManager::Enqueue(WP_LogMessage _message)
{
	std::lock_guard lock(m_queueMutex);
	m_logQueue.push(std::move(_message));

	//notify condition variable for runlogqueue to run
	m_conditionVariable.notify_one();
}

void WP_LogManager::RunLogQueue()
{
	//log file
	std::ofstream file("errors.log", std::ios::app);

	while (true) {
		std::unique_lock<std::mutex> lock(m_queueMutex);


		//will wait for condition variable to notify, and will only continue if the lambda returns true
		//equivilant to return this->m_isStopping || !this->m_logQueue.empty();
		m_conditionVariable.wait(lock, [this] { return m_isStopping || !m_logQueue.empty(); });

		//clear queue before stopping thread so we dont miss any log messages
		if (m_isStopping && m_logQueue.empty())
		{
			return;
		}

		auto message = std::move(m_logQueue.front());
		m_logQueue.pop();

		lock.unlock();

		std::cout << message.p_text;

		if (message.p_level == WP_LogLevel::Error)
			file << message.p_text;

	}
}