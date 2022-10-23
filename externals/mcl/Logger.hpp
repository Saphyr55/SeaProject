#pragma once

#include <string>
#include <iostream>

namespace mcl
{
    class Log
    {
    private:
        enum class LogSeverity;
        enum class ColorLogger;

    public:
        static Log Warning();
        static Log Debug();
        static Log Info();
        static Log Error();

    private:
        Log(LogSeverity severity, ColorLogger color);

    public:
        ~Log();

    public:
        template <typename T>
        Log& operator<<(T& s)
        {
            std::cout << s;
            return *this;
        }

        template <typename T>
        Log& operator<<(const T &s)
        {
            std::cout << s;
            return *this;
        }

    private:
        void send();
        static const char *severity_to_string(LogSeverity &property);
        const std::string currentDateTimeLogger();
        std::string to_ANSI(ColorLogger color);

        enum class ColorLogger
        {
            YELLOW,
            WHITE,
            RED,
            GREEN
        };

        enum class LogSeverity
        {
            INFO,
            WARNING,
            _ERROR,
            DEBUG
        };

        LogSeverity severity;
        ColorLogger color;
    };

}