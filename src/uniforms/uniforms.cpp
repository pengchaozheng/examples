#include "vgl.h"
#include "LoadShaders.h"
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
const char* vShader = {
	"#version 330 core\n"
	"uniform Uniforms {"
	"	vec3 translation;"
	"	float scale;"
	"	vec4 rotation;"
	"	bool  enabled;"
	"	};"
	"in vec2 vPos;"
	"in vec3 vColor;"
	"out vec4 fColor;"
	"void main()"
	"{"
	"	vec3	pos = vec3(vPos,0.0);"
	"	float angle = radians(rotation[0]);"
	"	vec3 axis = normalize(rotation.yzw);"
	"	mat3 I = mat3(1.0);"
	"	mat3 S = mat3(	0,	-axis.z,	axis.y, "
	"					axis.z,	0,	-axis.x,"
	"					-axis.y,	axis.x,	0);"
	"	mat3 uut = outerProduct(axis,axis);"
	"	mat3 rot = uut + cos(angle)*(I - uut)+ sin(angle)*S;"
	"	pos *= scale;"
	"	pos *= rot;"
	"	pos += translation;"
	"	fColor = vec4(scale,scale,scale,1);"
	"	gl_Position = vec4(pos,1);"
	"}"
};
const char* fShader = {
	"#version 330 core\n"
	"uniform Uniforms {"
	"	vec3 translation;"
	"	float scale;"
	"	vec4 rotation;"
	"	bool enabled;"
	"};"
	"in vec4 fColor;"
	"out vec4 color;"
	"void main()"
	"{"
	"	color = fColor;"
	"}"
};



size_t
TypeSize(GLenum type) {
	size_t size;
#define CASE(Enum,Count,Type) \
case Enum : size = Count*sizeof(Type);break;
	switch (type) {
		CASE(GL_FLOAT, 1, GLfloat);
		CASE(GL_FLOAT_VEC2, 2, GLfloat);
		CASE(GL_FLOAT_VEC3, 3, GLfloat);
		CASE(GL_FLOAT_VEC4, 4, GLfloat);
		CASE(GL_INT, 1, GLint);
		CASE(GL_INT_VEC2, 2, GLint);
		CASE(GL_INT_VEC3, 3, GLint);
		CASE(GL_INT_VEC4, 4, GLint);
		CASE(GL_UNSIGNED_INT,1,GLuint);
		CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
		CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
		CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
		CASE(GL_BOOL, 1, GLboolean);
		CASE(GL_BOOL_VEC2, 2, GLboolean);
		CASE(GL_BOOL_VEC3, 3, GLboolean);
		CASE(GL_BOOL_VEC4, 4, GLboolean);
#undef CASE
	default:
		fprintf(stderr,"Unknown type:	0x%x\n",type);
		exit(-1);
		break;

	}
	return size;
}

void init() {
	GLuint program;
	glClearColor(1,0,0,1);
	ShaderInfo shader[] = {
		{GL_VERTEX_SHADER,vShader,0},
		{GL_FRAGMENT_SHADER,fShader,0},
		{GL_NONE,NULL	,0}
	};
	program = LoadShaders(shader);
	glUseProgram(program);
	GLuint uboIndex;
	GLint uboSize;
	GLuint ubo;
	GLfloat	*buffer = NULL;
	uboIndex = glGetUniformBlockIndex(program,"Uniforms");

	//获取block属性
	glGetActiveUniformBlockiv(program, uboIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
	buffer = (GLfloat*)malloc(uboSize);
	if (NULL == buffer) {
		fprintf(stderr,"Unable to allocate buffer\n");
		exit(-1);
	}
	else {
		enum {Translation,Scale,Rotation,Enabled,NumUniforms};
		GLfloat scale = 0.5;
		GLfloat translation[] = {0.1,0.1,0.0};
		GLfloat rotation[]= {90,0.0,0.0,1.0};
		GLboolean enabled = GL_TRUE;

		const char* names[NumUniforms] = {
			"translation"
			,"scale"
			,"rotation"
			,"enabled"
		};

		GLuint indices[NumUniforms];
		GLint size[NumUniforms];
		GLint offset[NumUniforms];
		GLint type[NumUniforms];

		//获取uniform属性
		glGetUniformIndices(program,NumUniforms,names,indices);
		glGetActiveUniformsiv(program,NumUniforms,indices,GL_UNIFORM_OFFSET,offset);
		glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
		glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);

		memcpy(buffer+	offset[Scale],&scale,size[Scale]*TypeSize(type[Scale]));
		memcpy(buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
		memcpy(buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));
		memcpy(buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Enabled]));
	
		glGenBuffers(1,&ubo);
		glBindBuffer(GL_UNIFORM_BUFFER,ubo);
		glBufferData(GL_UNIFORM_BUFFER,uboSize,buffer,GL_STATIC_READ);
		glBindBufferBase(GL_UNIFORM_BUFFER,uboIndex,ubo);
	}
}


void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);

	//glBindVertexArray(VAOs[Triangles]);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

//----------------------------------------------------------------------------
//
// main
//

#ifdef _WIN32
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
#else
int
main(int argc, char** argv)
#endif
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit();

	init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}