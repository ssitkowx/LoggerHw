#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <chrono>
#include "Utils.h"
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "Logger.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define LOG(MODULE,MSG, ...)  Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::None   , MODULE, MSG, ##__VA_ARGS__);
#define LOGE(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::Error  , MODULE, MSG, ##__VA_ARGS__);
#define LOGW(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::Warning, MODULE, MSG, ##__VA_ARGS__);
#define LOGI(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::Info   , MODULE, MSG, ##__VA_ARGS__);
#define LOGD(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::Debug  , MODULE, MSG, ##__VA_ARGS__);
#define LOGV(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerHw> (Logger::ELogLevel::Verbose, MODULE, MSG, ##__VA_ARGS__);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LoggerHw : public Logger
{
    private:
        struct Color
        {
            static constexpr char black  [] = "\033[0;30m";
            static constexpr char red    [] = "\033[0;31m";
            static constexpr char green  [] = "\033[0;32m";
            static constexpr char yellow [] = "\033[0;33m";
            static constexpr char blue   [] = "\033[0;34m";
            static constexpr char purple [] = "\033[0;35m";
            static constexpr char cyan   [] = "\033[0;36m";
            static constexpr char white  [] = "\033[0;37m";
        };
        static std::mutex mutex;
        Color             color;

        constexpr std::string_view getFontColor (const ELogLevel v_eLogLevel)
        {
            switch (v_eLogLevel)
            {
                case ELogLevel::None:    { return color.white;  }
                case ELogLevel::Error:   { return color.red;    }
                case ELogLevel::Warning: { return color.purple; }
                case ELogLevel::Info:    { return color.blue;   }
                case ELogLevel::Debug:   { return color.yellow; }
                case ELogLevel::Verbose: { return color.green;  }
                default:                 { break;               }
            };

            return color.white;
        }

        auto getCurrentTime (void)
        {
            auto        now  = std::chrono::system_clock::now ();
            std::time_t time = std::chrono::system_clock::to_time_t (now);
            return std::put_time (std::localtime (&time), "%Y-%m-%d %H:%M:%S");
        }

    public:
        template<typename... ARGS>
        void Log (const ELogLevel vLogLevel, std::string vModule, std::string vMsg, ARGS &&... vArgs)
        {
            std::lock_guard<std::mutex> guard (mutex);
            const std::string msg = std::move (Format (vMsg.data (), std::forward<ARGS>(vArgs)...));

            std::cout << color.blue << vModule
                      << " "
                      << color.purple
                      << getCurrentTime ()
                      << getFontColor (vLogLevel)
                      << " "
                      << msg
                      << color.white << std::endl;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
