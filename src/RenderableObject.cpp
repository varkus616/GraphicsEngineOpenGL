#include <RenderableObject.hpp>


RenderableObject::RenderableObject(Mesh* mesh, DrawMode mode) : m_drawMode(mode)
{
    if (mesh != nullptr)
        m_meshes.push_back(mesh);
}
    
void RenderableObject::draw(RenderTarget& target, RenderData& data)
{
    for (size_t i = 0; i < m_meshes.size(); i++) {
        auto& mesh = m_meshes[i];
        if (mesh != nullptr) {
            mesh->setupBuffers();
            //mesh->bindTextures();
            data.drawMode = m_drawMode;

            target.draw(mesh->getBuffer(), mesh->getIndexBuffer(), data);

            //mesh->unbindTextures();
            mesh->getVertexArray().Reset();
        }
    }
}
glm::mat4& RenderableObject::getModelMatrix() {
    if (transform.dirty) {
        updateModelMatrix();
        transform.dirty = false;
    }
    return transform.modelMatrix;
}

void RenderableObject::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
}

void RenderableObject::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh* RenderableObject::processMesh(aiMesh* mesh, const aiScene* scene)
{
    //std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    //std::vector<GLfloat> textCoords;


    std::vector<Vertex> vertexes;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex v;
        v.Position.x = mesh->mVertices[i].x;
        v.Position.y = mesh->mVertices[i].y;
        v.Position.z = mesh->mVertices[i].z;
        //vertices.push_back(mesh->mVertices[i].x);
        //vertices.push_back(mesh->mVertices[i].y);
        //vertices.push_back(mesh->mVertices[i].z);

        // normals
        if (mesh->HasNormals())
        {
            //v.Position.x = mesh->mNormals[i].x;
            //v.Position.x = mesh->mNormals[i].y;
            //v.Position.x = mesh->mNormals[i].z;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            //v.TextureCoords.x = mesh->mTextureCoords[0][i].x;
            //v.TextureCoords.y = mesh->mTextureCoords[0][i].y;
            //textCoords.push_back(mesh->mTextureCoords[0][i].x);
            //textCoords.push_back(mesh->mTextureCoords[0][i].y);
        }
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
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
    std::cout << "INDI:" << mesh->mNumFaces << " " << "VERT:" << mesh->mNumVertices << std::endl;
    return new Mesh(vertexes, indices);
}

void RenderableObject::setColor(const glm::vec4& color) {
    
    this->color = color;
}