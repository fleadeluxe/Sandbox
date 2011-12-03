//
//  LogTypes.h
//  Sandbox
//
//  Created by Jack Smith on 3/12/11.
//  Copyright (c) 2011 --. All rights reserved.
//

#ifndef Sandbox_LogTypes_h
#define Sandbox_LogTypes_h

struct SSourceInfo
{
    SSourceInfo(const char* p_szFileName,
                int         p_nFileLine,
                const char* p_szFuncName)
    : m_sFileName(p_szFileName)
    , m_nFileLine(p_nFileLine)
    , m_sFuncName(p_szFuncName)
    {}
    
    std::string m_sFileName;
    std::string m_sFuncName;
    
    int         m_nFileLine;
};

#endif
