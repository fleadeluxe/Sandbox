//
//  Logger.cpp
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011 --. All rights reserved.
//

#include "Logger.h"
#include <stdarg.h>
#include <sstream>

#define MAX_BUFFER_SIZE 2048

CLogger::CLogger(const char* p_szFileName)
: m_bOpen(false)
{
    m_LogFile.open(p_szFileName);
    m_bOpen = m_LogFile.is_open();
}

CLogger::~CLogger()
{
    m_LogFile.close();
}

void CLogger::LogWithArgs(const SSourceInfo& p_rsSourceInfo,
                          const char*        p_szFormat,
                          ...)
{
    if (!m_bOpen)
        return;
    
    char buff[MAX_BUFFER_SIZE];
    va_list apList;
    va_start(apList, p_szFormat);
    vsnprintf(buff, MAX_BUFFER_SIZE, p_szFormat, apList);
    va_end(apList);
    
    Log(p_rsSourceInfo, buff);
}

void CLogger::Log(const SSourceInfo &p_rsSourceInfo, const char *p_szMsg)
{
    if (!m_bOpen)
        return;
    
    m_LogFile << __TIMESTAMP__ << "\t" << p_rsSourceInfo.m_sFileName
                << " (" << p_rsSourceInfo.m_nFileLine << "): "
                << p_rsSourceInfo.m_sFuncName << "(): " << p_szMsg << std::endl;
    
    m_LogFile.flush();
}