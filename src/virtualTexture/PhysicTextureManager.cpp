#include "PhysicTextureManager.h"
PhysicTextureManager::PhysicTextureManager(GLsizei k, GLsizei tileSize, GLsizei tileCount,GLenum tileFormat = GL_RGBA, GLsizei maxMipmapLevel = 11, GLuint priorMipLevel = 3) {
	GLuint* texIds = new GLuint[tileSize+1];
	if (NULL != texIds) {
		glGenTextures(tileCount + 2, texIds);
		texId = texIds[0];
	}
	GLuint width = (tileCount + 1) / 2;
	tileRows = 2;
	tileColumns = width;
	for (int i = 0; i < tileCount; i++) {
		PhysicTileInfo* data = new PhysicTileInfo;
		if (NULL == data) {
			fprintf(stderr,"Init TieInfo Failed id %d\n"+i);
			return;
		}
		data->id = i;
		data->texName = texIds[i + 1];
		data->size = tileCount;
		data->offsetX = i % width;
		data->offsetY = i / width;
		data->mipmapMask = 0;
		data->interFormat = tileFormat;
		tileInfoMap[i] = data;
	}
}
void PhysicTextureManager::initPhysicTexture(
	GLuint texId,GLuint arrayId,GLuint* tileIds
	,GLsizei tileRows,GLsizei tileColumns
	,GLsizei tileCount,GLsizei tileSize
	,GLuint mipMapLevers, GLenum texFormat) {
	GLenum errorID = GL_NO_ERROR;
	glBindTexture(GL_TEXTURE_2D_ARRAY, arrayId);
	glTextureStorage3D(GL_TEXTURE_2D_ARRAY,mipMapLevers,texFormat,tileSize,tileSize,tileCount);
	errorID = glGetError();
	if (GL_NO_ERROR == errorID) {
		fprintf(stderr,"Init Physic ArrayTexture Success!\n");
	}
	else {
		fprintf(stderr,"init Physic ArrayTexture Failed! Error id:%d\n", errorID);
	}
	//创建物理贴图的整张贴图试图
	glTextureView(texId
	,GL_TEXTURE_2D
	,texArrayId
	,texFormat
	,0,mipMapLevers
	,0,tileCount);
	errorID = glGetError();
	if (GL_NO_ERROR == errorID ) {
		fprintf(stderr,"Init Physic textureView Success!");
	}
	else {
		fprintf(stderr,"init Physic textureView Failed! Error id:%d\n", errorID);
	}
}




void PhysicTextureManager::init(GLuint arrayTexId,PhysicTileInfo* info) {
	if (NULL == info) {
		fprintf(stderr,"Tile Info Is NULL!\n");
		return;
	}
	glTextureView(info->texName
		,GL_TEXTURE_2D
	,arrayTexId,info->interFormat
	,0,11
	,0,100);

}


PhysicTextureManager::~PhysicTextureManager() {

}


GLuint PhysicTextureManager::getTileSize() {
}
GLuint PhysicTextureManager::getTileCount() {

}
const PhysicTileInfo* PhysicTextureManager::getTileInfo(GLuint id) {

}
GLuint PhysicTextureManager::getValideTileId() {

}