#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "objloader.hpp"
#include <iostream>

using std::string;
using std::vector;
using std::find;
using std::cout;
using std::endl;

bool loadAssImp(
    const aiMesh* mesh, 
	vector<unsigned short> & indices,
	vector<glm::vec3> & vertices,
	vector<glm::vec2> & uvs,
	vector<glm::vec3> & normals,
    int offset
){
	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}
	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}
	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]+offset);
		indices.push_back(mesh->mFaces[i].mIndices[1]+offset);
		indices.push_back(mesh->mFaces[i].mIndices[2]+offset);
	}
	// The "scene" pointer will be deleted automatically by "importer"
    return true;
}
