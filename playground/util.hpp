#ifndef HEADER
#define HEADER
#include <GL/glew.h>
#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
#else
	#include <GL/gl.h>
#endif

#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <typeinfo>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include <assert.h>

#include <map>
#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/anim.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <common/texture.hpp>

std::string loadTextFile(std::string path);
GLuint getShaderId(std::string path, GLuint shader_type);
GLuint getProgramId(std::string path_vs, std::string path_fs);

struct VertexData
{
	GLfloat position[3];
	GLfloat position2[3];
	GLfloat normal[3];
	GLfloat textureCoord[2];
	GLfloat boneWeights[4];
	GLfloat boneIDs[4];
};

struct VertexData2
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat textureCoord[2];
};

void printAssimpMatrix4x4(aiMatrix4x4 *matrix);
double getAlpha(double aiKeyN_time, double aiKeyN1_time, double animation_time);
void buildNodeHierarchy(const aiNode *node, std::map<std::string, int>& bone_name_hash, const glm::mat4 &T, std::vector<glm::mat4> &bone_transforms);
void printMat4(glm::mat4 &to);
void copyAiMatrixToGLM(const aiMatrix4x4 *from, glm::mat4 &to);
#endif
