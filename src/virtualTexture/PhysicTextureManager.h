#pragma once
#include <vermilion.h>
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vmath.h"
#include <stdio.h>


struct PhysicTileInfo {
	GLuint id;
	GLushort mipmapMask;//MipMap加载层级信息
	GLuint offsetX;//在物理贴图的中的偏移量
	GLuint offsetY;//在物理贴图中的偏移量
	GLsizei size;//
};


enum PhysicTileType {
	Array,//数组形式

};

class PhysicTextureManager
{
private:
//物理贴图的实际大小
	GLsizei textureWidth;
	GLsizei textureHeight;
private:
	GLsizei tileSize;//每个分块的大小
	GLsizei tileCount;//分块的数量

private:
	GLsizei PriorMipmapLevel;//分块有限加载mipmap层级
private:
};

