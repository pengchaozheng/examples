
#define USE_GL3W
#include <vermilion.h>
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vmath.h"
#include <stdio.h>

#include <string.h>
using namespace std;
#pragma once


struct VirtualImage {
	GLuint poxX;
	GLuint poxY;
	GLuint width;
	GLuint height;
	GLuint mipMap;
	//string  path;
};
class VirtualTextureManager
{
public:
	GLuint width;
	GLuint height;



};
