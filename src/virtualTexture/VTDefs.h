#include <vermilion.h>
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vmath.h"
#include <stdio.h>
#pragma once
struct PhysicTileInfo {
	GLuint id;
	GLuint texName;//opengl�����texture��id
	GLenum interFormat;//������ڲ���ʽ
	GLushort mipmapMask;//MipMap�Ѿ����ز㼶
	GLuint offsetX;//��������ͼ���е�ƫ����
	GLuint offsetY;//��������ͼ�е�ƫ����
	GLsizei size;//��С
};

//
//enum PhysicMapFormat {
//	Array,//������ʽ
//	TileMap,//��ΪTile��ʽ
//};