/*
    Logging system for application
	Run logging in a separate thread to avoid blocking the main thread for expensive io operations
*/

#pragma once
#include <string>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>

enum class WP_LogLevel
{
	Info,
	Warning,
	Error
};

struct WP_LogMessage
{
    WP_LogMessage(WP_LogLevel _level, std::string _text)
		: p_level(_level), p_text(std::move(_text)) {}

    std::string p_text;
    WP_LogLevel p_level;
};

class WP_LogManager
{
public:

    static WP_LogManager& GetInstance();

	WP_LogManager() :
		m_logThread(&WP_LogManager::RunLogQueue, this), 
		m_isStopping(false){}

    void Enqueue(WP_LogMessage _message);

    void Stop();
private:
    void RunLogQueue();

	std::queue<WP_LogMessage> m_logQueue;
	std::mutex m_queueMutex;
	std::condition_variable m_conditionVariable;
	std::thread m_logThread;
	bool m_isStopping;
};


class WP_Logger
{
public:
    //default set as information log level
    WP_Logger(WP_LogLevel level = WP_LogLevel::Info)
        : m_level(level)
    {
    }

    template <typename T>
    WP_Logger& operator<<(const T& value) {
        m_buffer << value;
        return *this;
    }

    ~WP_Logger() {
        WP_LogManager::GetInstance().Enqueue({
            m_level,
            m_buffer.str()
            });
    }

private:
    WP_LogLevel m_level;
    std::ostringstream m_buffer;
};
