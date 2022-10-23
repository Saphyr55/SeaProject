#include <iostream>
#include <stdio.h>
#include <time.h>
#include <mcl/Logger.hpp>

namespace mcl
{
    Log Log::Warning() { return Log(LogSeverity::WARNING, ColorLogger::YELLOW); }
    Log Log::Debug() { return Log(LogSeverity::DEBUG, ColorLogger::GREEN); }
    Log Log::Info() { return Log(LogSeverity::INFO, ColorLogger::WHITE); }
    Log Log::Error() { return Log(LogSeverity::_ERROR, ColorLogger::RED); }

    Log::Log(LogSeverity severity, ColorLogger color)
    {
        this->severity = severity;
        this->color = color;
        Log::send();
    }

    Log::~Log() { std::cout << "\033[0m\n"; }

    const std::string Log::currentDateTimeLogger()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);
        return buf;
    }

    void Log::send()
    {
        std::cout << "[ " << currentDateTimeLogger() << " ] ";
        std::cout << to_ANSI(color) << severity_to_string(severity) << " : ";
    }

    const char *Log::severity_to_string(LogSeverity &property)
    {
        switch (property)
        {
        case LogSeverity::_ERROR:
            return "ERROR";
        case LogSeverity::DEBUG:
            return "DEBUG";
        case LogSeverity::INFO:
            return "INFO";
        case LogSeverity::WARNING:
            return "WARNING";
        default:
            return "INFO";
        }
    }

    std::string Log::to_ANSI(ColorLogger color)
    {
        switch (color)
        {
        case ColorLogger::WHITE:
            return "\033[0;97m";
        case ColorLogger::YELLOW:
            return "\033[0;93m";
        case ColorLogger::RED:
            return "\033[0;91m";
        case ColorLogger::GREEN:
            return "\033[0;92m";
        default:
            return "\033[0;97m";
        }
    }
}