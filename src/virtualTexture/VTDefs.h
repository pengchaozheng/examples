#include <vermilion.h>
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vmath.h"
#include <stdio.h>
#pragma once
struct PhysicTileInfo {
	GLuint id;
	GLuint texName;//opengl分配给texture的id
	GLenum interFormat;//纹理的内部格式
	GLushort mipmapMask;//MipMap已经加载层级
	GLuint offsetX;//在物理贴图的中的偏移量
	GLuint offsetY;//在物理贴图中的偏移量
	GLsizei size;//大小
};

//
//enum PhysicMapFormat {
//	Array,//数组形式
//	TileMap,//分为Tile形式
//};