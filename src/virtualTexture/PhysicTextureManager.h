#pragma once
#include"VTDefs.h"
#include<hash_map>
using namespace std;






//������ͼ�ṩÿ����ͼ��
class PhysicTextureManager
{
	struct TileInfoInternal {
		GLuint id;
		GLuint texName;
		GLchar* pTilePointer;
	};
private:
	hash_map<int, PhysicTileInfo*> tileInfoMap;
private:
	GLsizei tileSize;//ÿ���ֿ�Ĵ�С
	GLsizei tileCount;//�ֿ������
	GLsizei tileColumns;//�ֿ������
	GLsizei tileRows;//�ֿ������
private:
	GLsizei PriorMipmapLevel;//�ֿ����޼���mipmap�㼶
private:
	GLsizei maxMipmapLevel;//����MipMap�㼶
//private:
//PhysicMapFormat format;//������ͼ�ĸ�ʽ
private:
	GLuint texId;//������ͼ������ͼ����ͼ�����id
	GLuint texArrayId;//������ͼtexture2DArray������
public:
	//PhysicTextureManager(GLsizei k,GLsizei tileCount,GLuint priorMipLevel,PhysicMapFormat format = PhysicMapFormat::TileMap);
	PhysicTextureManager(GLsizei k,GLsizei tileSize, GLsizei tileCount, GLenum tileFormat = GL_RGBA,   GLsizei maxMipmapLevel = 11, GLuint priorMipLevel=3);
	~PhysicTextureManager();
public:
	GLuint getTileSize();
	GLuint getTileCount();
	const PhysicTileInfo* getTileInfo(GLuint id);
	GLuint getValideTileId();
private:
	void initPhysicTexture(GLuint texId, GLuint arrayId, GLuint* tileIds,  GLsizei tileRows, GLsizei tileColumns ,GLsizei tileCount, GLsizei tileSize, GLuint mipMapLevers, GLenum texFormat);
	void init(GLuint arrayTexId,PhysicTileInfo* info);
};


