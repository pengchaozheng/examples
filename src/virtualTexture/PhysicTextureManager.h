#pragma once
#include <vermilion.h>
#include "vapp.h"
#include "vutils.h"
#include "vbm.h"
#include "vmath.h"
#include <stdio.h>


struct PhysicTileInfo {
	GLuint id;
	GLushort mipmapMask;//MipMap���ز㼶��Ϣ
	GLuint offsetX;//��������ͼ���е�ƫ����
	GLuint offsetY;//��������ͼ�е�ƫ����
	GLsizei size;//
};


enum PhysicTileType {
	Array,//������ʽ

};

class PhysicTextureManager
{
private:
//������ͼ��ʵ�ʴ�С
	GLsizei textureWidth;
	GLsizei textureHeight;
private:
	GLsizei tileSize;//ÿ���ֿ�Ĵ�С
	GLsizei tileCount;//�ֿ������

private:
	GLsizei PriorMipmapLevel;//�ֿ����޼���mipmap�㼶
private:
};

