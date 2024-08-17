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
                case ELogLevel::None:    { return ColorWhite;  }
                case ELogLevel::Error:   { return ColorRed;    }
                case ELogLevel::Warning: { return ColorPurple; }
                case ELogLevel::Info:    { return ColorBlue;   }
                case ELogLevel::Debug:   { return ColorYellow; }
                case ELogLevel::Verbose: { return ColorGreen;  }
                default:                  { break;              }
            };

            return ColorWhite;
        }
    public:

        template<typename... ARGS>
        void Log (const ELogLevel vLogLevel, std::string_view vModule, std::string_view vMsg, ARGS &&... vArgs)
        {
            std::cout << ColorBlue << vModule.data ()
                      << getFontColor (vLogLevel)
                      << " "
                      << vMsg.data ()
                      << " ";
          ((std::cout << std::forward <ARGS> (vArgs)), ...);
            std::cout << ColorWhite << std::endl;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
