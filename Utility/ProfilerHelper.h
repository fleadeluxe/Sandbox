/*
 *  ProfilerHelper.h
 *  Sandbox
 *
 *  Created by Jack Smith on 13/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#ifndef PROFILER_HELPER_H_INCLUDED
#define PROFILER_HELPER_H_INCLUDED

#include "Profiler.h"

static CProfiler g_Profiler;

class CProfileSample
{
public:
	CProfileSample(const char* p_szName)
	{
		g_Profiler.StartProfile(p_szName);
	}
	
	~CProfileSample()
	{
		g_Profiler.StopProfile();
	}
};

#define PROFILE(name) CProfileSample __profile(name)
#define PROFILER_NEW_FRAME	g_Profiler.StartFrame()

#endif //PROFILER_HELPER_H_INCLUDED