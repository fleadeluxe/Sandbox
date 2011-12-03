//
//  Logger.h
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011 --. All rights reserved.
//

#ifndef Sandbox_Logger_h
#define Sandbox_Logger_h

#include <string.h>
#include <stdarg.h>
#include <fstream.h>

#include "LogTypes.h"

class CLogger
{
public:
    CLogger(const char* p_szFileName);
    ~CLogger();
    void LogWithArgs(const SSourceInfo& p_rsSourceInfo,
                     const char*        p_szFormat,
                     ...);
    void Log(const SSourceInfo& p_rsSourceInfo,
             const char*        p_szMsg);
    
private:
    std::ofstream m_LogFile;
    bool            m_bOpen;
};

extern CLogger* g_pLogger;

#define VLOG(format, ...)                               \
        g_pLogger->LogWithArgs(SSourceInfo(__FILE__,    \
                                    __LINE__,           \
                                    __FUNCTION__),      \
                        format,                         \
                        __VA_ARGS__)                    \

#define LOG(msg)                                        \
        g_pLogger->Log(SSourceInfo(__FILE__,            \
                                    __LINE__,           \
                                    __FUNCTION__),      \
                        msg)                            \

#endif
