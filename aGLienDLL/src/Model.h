﻿/*
Kod zaczerpnięty i edytowany na licencji CC BY-NC 4.0
Źródło: https://learnopengl.com/Model-Loading/Model
Autor: Joey de Vries (twitter.com/JoeyDeVriez)
Licencja: https://creativecommons.org/licenses/by-nc/4.0/legalcode
*/

#ifndef MODEL_H
#define MODEL_H



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Mesh.h"
using namespace std;

__declspec(dllexport) unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class __declspec(dllexport) Model
{
public:
    // model data 
    vector<MeshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;
    
    // constructor, expects a filepath to a 3D model.
    Model(string const& path, bool gamma = false); 
    // draws the model, and thus all its meshes
    void Draw(Shader& shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path);
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

};


__declspec(dllexport) unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
#endif