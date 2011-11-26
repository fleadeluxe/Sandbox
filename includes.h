/*
 *  includes.h
 *  Sandbox
 *
 *  Created by Jack Smith on 6/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

//System
#include <unistd.h>
#include <iostream>

//SDL
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_syswm.h"
#include "SDL_quit.h"

//Math
#include <glm.hpp>
#include <type_ptr.hpp>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif //INCLUDES_H_INCLUDED