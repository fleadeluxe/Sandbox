/*
 *  Utilities.h
 *  Sandbox
 *
 *  Created by Jack Smith on 13/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

static float GetTime()
{
	static int32_t nStart = 0;
	
	if (nStart == 0)
	{
		nStart = SDL_GetTicks();
		return 0.0f;
	}
	
	int32_t nCurrent = SDL_GetTicks();
	return (nCurrent-nStart)/1000.0f;
}

#endif //UTILITIES_H_INCLUDED