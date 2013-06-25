#include "util.hpp"

std::string loadTextFile(std::string path)
{
	std::ifstream in(path.c_str(), std::ifstream::in);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	return contents;
}

GLuint getShaderId(std::string path, GLuint shader_type)
{
	std::string shader_src=loadTextFile(path);
	GLuint shader = glCreateShader(shader_type);
	char const *shader_src_pointer=shader_src.c_str();
	glShaderSource(shader, 1, &shader_src_pointer, NULL);
	glCompileShader(shader);
	GLint compiled;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLint blen = 0;
		GLsizei slen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &blen);
		if(blen > 1)
		{
			GLchar* compiler_log = (GLchar*)malloc(blen);
			glGetShaderInfoLog(shader, blen, &slen, compiler_log);
			std::cout << "Compiler log:\n" << compiler_log;
			free(compiler_log);
		}
		exit(1);
	}
	else
	{
		std::cout << "Shader compiled!" << std::endl;
	}
	return shader;
}


GLuint getProgramId(std::string path_vs, std::string path_fs)
{
	GLuint vs = getShaderId(path_vs, GL_VERTEX_SHADER);
	GLuint fs = getShaderId(path_fs, GL_FRAGMENT_SHADER);

	GLuint programId = glCreateProgram();

	glAttachShader(programId, vs);
	glAttachShader(programId, fs);

	glLinkProgram(programId);

	return programId;
}

void printAssimpMatrix4x4(aiMatrix4x4 *matrix)
{
	std::cout << matrix->a1 << " " << matrix->a2 << " " << matrix->a3 << " " << matrix->a4 << std::endl;
	std::cout << matrix->b1 << " " << matrix->b2 << " " << matrix->b3 << " " << matrix->b4 << std::endl;
	std::cout << matrix->c1 << " " << matrix->c2 << " " << matrix->c3 << " " << matrix->c4 << std::endl;
	std::cout << matrix->d1 << " " << matrix->d2 << " " << matrix->d3 << " " << matrix->d4 << std::endl;
}

double getAlpha(double aiKeyN_time, double aiKeyN1_time, double animation_time)
{
	double p = aiKeyN1_time - aiKeyN_time;
	if (p < 0.00005) return 1;
	return (animation_time - aiKeyN_time)/p;
}

void buildNodeHierarchy(const aiNode *node, std::map<std::string, int>& bone_name_hash, const glm::mat4 &T, std::vector<glm::mat4> &bone_transforms)
{
	glm::mat4 current_node_transform = T;
	if (&(node->mName) != NULL)
	{
		std::map<std::string, int>::iterator it = bone_name_hash.find(node->mName.data);
		if (it != bone_name_hash.end())
		{
			current_node_transform = current_node_transform * bone_transforms[it->second];
			bone_transforms[it->second] = current_node_transform;
		}
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		buildNodeHierarchy(node->mChildren[i], bone_name_hash, current_node_transform, bone_transforms);
}

void printMat4(glm::mat4 &to)
{
	std::cout << to[0][0] << " " << to[1][0] << " " << to[2][0] << " " << to[3][0] << std::endl;
	std::cout << to[0][1] << " " << to[1][1] << " " << to[2][1] << " " << to[3][1] << std::endl;
	std::cout << to[0][2] << " " << to[1][2] << " " << to[2][2] << " " << to[3][2] << std::endl;
	std::cout << to[0][3] << " " << to[1][3] << " " << to[2][3] << " " << to[3][3] << std::endl;
}


void copyAiMatrixToGLM(const aiMatrix4x4 *from, glm::mat4 &to) 
{
	to[0][0] = (GLfloat)from->a1; to[1][0] = (GLfloat)from->a2;
	to[2][0] = (GLfloat)from->a3; to[3][0] = (GLfloat)from->a4;
	to[0][1] = (GLfloat)from->b1; to[1][1] = (GLfloat)from->b2;
	to[2][1] = (GLfloat)from->b3; to[3][1] = (GLfloat)from->b4;
	to[0][2] = (GLfloat)from->c1; to[1][2] = (GLfloat)from->c2;
	to[2][2] = (GLfloat)from->c3; to[3][2] = (GLfloat)from->c4;
	to[0][3] = (GLfloat)from->d1; to[1][3] = (GLfloat)from->d2;
	to[2][3] = (GLfloat)from->d3; to[3][3] = (GLfloat)from->d4;
}
