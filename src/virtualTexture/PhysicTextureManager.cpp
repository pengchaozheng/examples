#include "PhysicTextureManager.h"
PhysicTextureManager::PhysicTextureManager(GLsizei k, GLsizei tileSize, GLsizei tileCount,GLenum tileFormat = GL_RGBA, GLsizei maxMipmapLevel = 11, GLuint priorMipLevel = 3) {
	GLuint* texIds = new GLuint[2];
	if (NULL != texIds) {
		glGenTextures(2, texIds);
		texArrayId = texIds[0];
		texId = texIds[1];
	}
	//初始化整张贴图和数组贴图
	GLenum errorID = GL_NO_ERROR;
	glBindTexture(GL_TEXTURE_2D_ARRAY, texArrayId);
	glTextureStorage3D(GL_TEXTURE_2D_ARRAY, maxMipmapLevel, tileFormat, tileSize, tileSize, tileCount);
	errorID = glGetError();
	if (GL_NO_ERROR == errorID) {
		fprintf(stderr, "Init Physic ArrayTexture Success!\n");
	}
	else {
		fprintf(stderr, "init Physic ArrayTexture Failed! Error id:%d\n", errorID);
	}

	glTextureView(texId
		, GL_TEXTURE_2D
		, texArrayId
		, tileFormat
		, 0, maxMipmapLevel
		, 0, tileCount);
	delete[] texIds;


	//初始化分块
	texIds = new GLuint[tileCount];
	if (NULL == texIds) {
		fprintf(stderr,"Init Tile Id Failed\n");
	}
	glGenTextures(tileSize,texIds);
	//创建物理贴图的整张贴图试图

	errorID = glGetError();
	if (GL_NO_ERROR == errorID) {
		fprintf(stderr, "Init Physic textureView Success!");
	}
	else {
		fprintf(stderr, "init Physic textureView Failed! Error id:%d\n", errorID);
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

		//每个分块提供一个问题贴图试图
		glTextureView(texArrayId
			,GL_TEXTURE_2D
			,texArrayId
			,tileFormat
			,0,11,
			i,1
		);
	}
}
void PhysicTextureManager::initPhysicTexture(
	GLuint texId,GLuint arrayId,GLuint* tileIds
	,GLsizei tileRows,GLsizei tileColumns
	,GLsizei tileCount,GLsizei tileSize
	,GLuint mipMapLevers, GLenum texFormat) {

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
	,info->id,1);

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