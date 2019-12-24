#ifndef INDIRECTTEXTURE
#define INDIRECTTEXTURE


#define USE_GL3W
#include <vermilion.h>

#include "vapp.h"
#include "vutils.h"
#include "vbm.h"

#include "vmath.h"

#include <stdio.h>


struct IndirectMapItem
{
	GLuint OffsetX;
	GLuint OffsetY;
	GLuint MipMap;
};

class IndirectManager {
private:
	IndirectMapItem* m_ppMaps[10];
public :
	void SetIndirect(GLfloat x, GLfloat y, GLuint mipMap, IndirectMapItem item);
	void GenerateMipmap();
};




#endif // !1


