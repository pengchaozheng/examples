#pragma once
#include"VTDefs.h"
#include<hash_map>
using namespace std;






//物理贴图提供每张贴图的
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
	GLsizei tileSize;//每个分块的大小
	GLsizei tileCount;//分块的数量
	GLsizei tileColumns;//分块的列数
	GLsizei tileRows;//分块的行数
private:
	GLsizei PriorMipmapLevel;//分块有限加载mipmap层级
private:
	GLsizei maxMipmapLevel;//最大的MipMap层级
//private:
//PhysicMapFormat format;//物理贴图的格式
private:
	GLuint texId;//物理贴图整张贴图的贴图对象的id
	GLuint texArrayId;//物体贴图texture2DArray对象名
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


