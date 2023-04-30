#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "Logger.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define LOG(MODULE,MSG, ...)  Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eNone   , MODULE, MSG, ##__VA_ARGS__);
#define LOGE(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eError  , MODULE, MSG, ##__VA_ARGS__);
#define LOGW(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eWarning, MODULE, MSG, ##__VA_ARGS__);
#define LOGI(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eInfo   , MODULE, MSG, ##__VA_ARGS__);
#define LOGD(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eDebug  , MODULE, MSG, ##__VA_ARGS__);
#define LOGV(MODULE,MSG, ...) Logger::GetInst ()->Log <LoggerMock> (Logger::ELogLevel::eVerbose, MODULE, MSG, ##__VA_ARGS__);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LoggerMock : public Logger
{
    private:
        static constexpr char ColorBlack  [] = "\033[0;30m";
        static constexpr char ColorRed    [] = "\033[0;31m";
        static constexpr char ColorGreen  [] = "\033[0;32m";
        static constexpr char ColorYellow [] = "\033[0;33m";
        static constexpr char ColorBlue   [] = "\033[0;34m";
        static constexpr char ColorPurple [] = "\033[0;35m";
        static constexpr char ColorCyan   [] = "\033[0;36m";
        static constexpr char ColorWhite  [] = "\033[0;37m";

        constexpr std::string_view getFontColor (const ELogLevel v_eLogLevel)
        {
            switch (v_eLogLevel)
            {
                case ELogLevel::eNone:    { return ColorWhite;  }
                case ELogLevel::eError:   { return ColorRed;    }
                case ELogLevel::eWarning: { return ColorPurple; }
                case ELogLevel::eInfo:    { return ColorBlue;   }
                case ELogLevel::eDebug:   { return ColorYellow; }
                case ELogLevel::eVerbose: { return ColorGreen;  }
                default:                  { break;              }
            };

            return ColorWhite;
        }
    public:

        template<typename... ARGS>
        void Log (const ELogLevel v_eLogLevel, std::string_view v_module, std::string_view v_msg, ARGS &&... v_args)
        {
            std::cout << ColorBlue << v_module.data ()
                      << getFontColor (v_eLogLevel)
                      << " "
                      << v_msg.data ()
                      << " ";
          ((std::cout << std::forward <ARGS> (v_args)), ...);
            std::cout << ColorWhite << std::endl;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
