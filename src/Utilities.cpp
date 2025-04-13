#include "Utilities.hpp"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <SOIL2/soil2.h>
#include <Mesh.hpp>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#define M_PI 3.14159265358979323846   


void Utils::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Utils::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "):" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

GLuint Utils::loadTexture(const char* texImagePath) {
    GLuint textureID;
    textureID = SOIL_load_OGL_texture(texImagePath,
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0) std::cout << "Warning: could not find texture file" << texImagePath << std::endl;
    GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat anisoSetting = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
    }


    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    return textureID;
}

std::string Utils::mat4ToString(const glm::mat4& matrix)
{
    std::ostringstream oss;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            oss << matrix[i][j];
            if (j < 3) oss << ", "; // Dodaj przecinek miêdzy elementami w wierszu
        }
        if (i < 3) oss << "\n"; // Dodaj now¹ liniê miêdzy wierszami
    }
    return oss.str();
}

std::string Utils::mat3ToString(const glm::mat3& matrix)
{
    std::ostringstream oss;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            oss << matrix[i][j];
            if (j < 2) oss << ", "; // Dodaj przecinek miêdzy elementami w wierszu
        }
        if (i < 2) oss << "\n"; // Dodaj now¹ liniê miêdzy wierszami
    }
    return oss.str();
}
std::string Utils::vec2ToString(const glm::vec2& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y;
    return oss.str();
}

std::string Utils::vec3ToString(const glm::vec3& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y << ", " << vector.z;
    return oss.str();
}

std::string Utils::vec4ToString(const glm::vec4& vector)
{
    std::ostringstream oss;
    oss << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w;
    return oss.str();
}

Mesh Utils::generatePlane(const int SIZE_X, const  int SIZE_Z)
{
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indices;

    int count = 0;
    int HALF_SIZE_X = SIZE_X / 2;
    int HALF_SIZE_Z = SIZE_Z / 2;
    float x, y, z = 0;

    for (int i = 0; i <= SIZE_Z; i++) {
        for (int j = 0; j <= SIZE_X; j++) {

            x, y, z = 0;
            
            //position
            x = ((float(j) / (SIZE_X - 1)) * 2 - 1) * HALF_SIZE_X;
            y = 0;
            z = ((float(i) / (SIZE_Z - 1)) * 2 - 1) * HALF_SIZE_Z;

            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //normals ( always point up duh ) 
            x, y, z = 0;
            y = 1.f;

            vertexData.push_back(x);
            vertexData.push_back(y);
            vertexData.push_back(z);
            
            //texture coords
            x = float(j) / SIZE_X;
            y = float(i) / SIZE_Z;


            vertexData.push_back(x);
            vertexData.push_back(y);
        }
    }
    
    for (int i = 0; i < SIZE_Z; i++) {
        for (int j = 0; j < SIZE_X; j++){
            int i0 = i * (SIZE_X + 1) + j;
            int i1 = i0 + 1;
            int i2 = i0 + (SIZE_X + 1);
            int i3 = i2 + 1;
            if ((j + i) % 2){
                indices.push_back(i0);
                indices.push_back(i2);
                indices.push_back(i1);


                indices.push_back(i1);
                indices.push_back(i2);
                indices.push_back(i3);
            }
            else {
                indices.push_back(i0);
                indices.push_back(i2);
                indices.push_back(i3);


                indices.push_back(i0);
                indices.push_back(i3);
                indices.push_back(i1);
            }
        }
    }
    VertexBufferLayout layout;
    layout.Push<GLfloat>(3);
    layout.Push<GLfloat>(3);
    layout.Push<GLfloat>(2);

    return Mesh(vertexData.data(), vertexData.size(), sizeof(GLfloat) , indices, layout);
}

void Utils::loadModel(std::string path, 
    std::vector<Mesh*>& meshes,
    std::vector<GLuint>& startIndincies)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Logger& logger = Logger::getInstance();
        std::stringstream ss;
        ss << "ERROR::ASSIMP::" << import.GetErrorString();
        logger.log(LogLevel::ERROR, ss.str());
        return;
    }
    processNode(scene->mRootNode, scene, meshes, startIndincies);
}

void Utils::processNode(aiNode* node, const aiScene* scene,
    std::vector<Mesh*>& meshes,
    std::vector<GLuint>& startIndincies)
{
    // process all the node's meshes (if any)
    int iSizeBefore = 0;
    const int VertexTotalSize = sizeof(aiVector3D)*2 + sizeof(aiVector2D);

    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE) {
            std::cerr << "Uwaga: Mesh nr: " << i << " nie jest triangulowana!" << std::endl;
            exit(1);
        }
        
        startIndincies.push_back(iSizeBefore / VertexTotalSize);
        
        auto mptr = processMesh(mesh, scene);
        meshes.push_back(mptr);
        
        iSizeBefore += mptr->getBuffer().GetSize() / sizeof(GLuint);
    }

    // then do the same for each of its children
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, 
            meshes, startIndincies);
    }
}

Mesh* Utils::processMesh(aiMesh* mesh, 
    const aiScene* scene)
{
    std::vector<GLuint> indices;
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normals;
        glm::vec2 TextureCoords;
    };

    std::vector<Vertex> vertexes;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex v;
        v.Position.x = mesh->mVertices[i].x;
        v.Position.y = mesh->mVertices[i].y;
        v.Position.z = mesh->mVertices[i].z;

        // normals
        if (mesh->HasNormals())
        {
            v.Normals.x = mesh->mNormals[i].x;
            v.Normals.y = mesh->mNormals[i].y;
            v.Normals.z = mesh->mNormals[i].z;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            v.TextureCoords.x = mesh->mTextureCoords[0][i].x;
            v.TextureCoords.y = mesh->mTextureCoords[0][i].y;
        }
        vertexes.push_back(v);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        if (face.mNumIndices != 3) {
            std::cerr << "B³¹d: Œciana " << i << " ma " << face.mNumIndices << " indeksów!" << std::endl;
            exit(1);
        }
        for (size_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    //vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //// 2. specular maps
    //vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //// 3. normal maps
    //std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //// 4. height maps
    //std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    VertexBufferLayout layout;
    layout.Push<GLfloat>(3);
    layout.Push<GLfloat>(3);
    layout.Push<GLfloat>(2);
    return new Mesh(vertexes.data(), vertexes.size(), sizeof(Vertex), indices, layout);
    
}







// GOLD material
glm::vec4* Utils::goldAmbient() { static glm::vec4 a = { 0.2473f, 0.1995f, 0.0745f, 1 }; return &a; }
glm::vec4* Utils::goldDiffuse() { static glm::vec4 a = { 0.7516f, 0.6065f, 0.2265f, 1 }; return &a; }
glm::vec4* Utils::goldSpecular() { static glm::vec4 a = { 0.6283f, 0.5558f, 0.3661f, 1 }; return &a; }
float Utils::goldShininess() { return 51.2f; }

// SILVER material - ambient, diffuse, specular, and shininess
float* Utils::silverAmbient() { static float a[4] = { 0.1923f, 0.1923f, 0.1923f, 1 }; return (float*)a; }
float* Utils::silverDiffuse() { static float a[4] = { 0.5075f, 0.5075f, 0.5075f, 1 }; return (float*)a; }
float* Utils::silverSpecular() { static float a[4] = { 0.5083f, 0.5083f, 0.5083f, 1 }; return (float*)a; }
float Utils::silverShininess() { return 51.2f; }

// BRONZE material - ambient, diffuse, specular, and shininess
float* Utils::bronzeAmbient() { static float a[4] = { 0.2125f, 0.1275f, 0.0540f, 1 }; return (float*)a; }
float* Utils::bronzeDiffuse() { static float a[4] = { 0.7140f, 0.4284f, 0.1814f, 1 }; return (float*)a; }
float* Utils::bronzeSpecular() { static float a[4] = { 0.3935f, 0.2719f, 0.1667f, 1 }; return (float*)a; }
float Utils::bronzeShininess() { return 25.6f; }