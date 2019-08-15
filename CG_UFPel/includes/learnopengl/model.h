#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <learnopengl/mesh.h>
#include <learnopengl/shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

const float OFFSET_START = 8.0f;
const float OFFSET_MOVE = 1.0f;
const float OFFSET_ROT = glm::radians(35.0f);

enum animation_t { none = 0, linear = 1, spline = 2, animation1 = 3, rotate_pt = 4};

typedef struct object_ {
  glm::vec3 scale;
  glm::quat rotation;
  glm::vec3 translation;

  animation_t anim;
  float time;
  float count;

  glm::mat4 mmod; // TODO get rid of
} object_t;

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
void print_vec(glm::vec3 v)
{ std::cout << "GET (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl; }
void print_quat(glm::quat q)
{ std::cout << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl; }

class Model 
{
  public:
    /*  Model Data */
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    // and a number of models to create
    Model(string const &path, unsigned n, bool gamma = false) : gammaCorrection(gamma)
    {
      loadModel(path);

      for (unsigned i = 0; i < n; ++i) {
        std::cout << "Creating models (" << i+1 << "/" << n << ")" << std::endl;
        object_t m;
        m.mmod = glm::mat4(1.0f);
        // it's a bit too big for our scene, so scale it down
        m.scale = glm::vec3(0.8f, 0.8f, 0.8f);
        // default rotation is no rotation
        m.rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
        // translate it down so it's at the center of the scene
        m.translation = glm::vec3(OFFSET_START * i, -0.5f, -10.0f); // planet

        // I don't need to scale it first, if a scale it everytime
        //m.mmod = glm::scale(m.mmod, m.scale);
        //m.mmod = glm::translate(m.mmod, m.translation);

        m.anim = animation_t::none;
        m.time = 0.0f;
        m.count = 0.0f;

        vobj.push_back(m);
      }

    }

    void translate_plus(glm::vec3 to)
    {
      if (this->vobj[this->slc_obj].anim != animation_t::none) return;
      this->vobj[this->slc_obj].translation += to;
    }

    // TODO delete
    //void rotate_in(glm::vec3 around, float dt)
    //{
    //  if (this->vobj[this->slc_obj].anim != animation_t::none) return;
    //  this->vobj[this->slc_obj].translation = around;
    //  this->vobj[this->slc_obj].rotation += dt * glm::vec3(1.0f, 0.0f, 1.0f);;
    //}

    void rotate_plus(glm::quat to)
    {
      if (this->vobj[this->slc_obj].anim != animation_t::none) return;
      this->vobj[this->slc_obj].rotation += to;
    }

    void scale_plus(glm::vec3 to)
    {
      if (this->vobj[this->slc_obj].anim != animation_t::none) return;
      glm::vec3 tmp = this->vobj[this->slc_obj].scale + to;
      if (tmp.x > 0.0f &&
          tmp.y > 0.0f &&
          tmp.z > 0.0f)
        this->vobj[this->slc_obj].scale = tmp;

    }

    void playRotation(float t, glm::vec3 in, object_t &obj)
    {
      if (obj.time <= 0.0f) {
        obj.rotation = (obj.count * glm::radians(45.0f)) * glm::quat(0.0f, 0.0f, 1.0f, 0.0f);

        obj.anim = animation_t::none;
        obj.time = 0.0f;
        obj.count = 0.0f;

        return;
      }

      obj.time -= t;
      obj.count += t;
      obj.mmod = glm::translate(obj.mmod, in); // move to the point
      obj.mmod = glm::rotate(obj.mmod, obj.count * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate
      obj.mmod = glm::translate(obj.mmod, glm::vec3(0, 0, 0) - in); // move back
      if (obj.time <= 0.0f) { // if it is the last time, move back to the original position n' save the new position
        obj.translation = glm::vec3(glm::translate(obj.mmod, obj.translation)[3]);
      }

    }

    void playLinear(float t, glm::vec3 ctrl_direction, object_t &obj)
    {
      if (obj.time <= 0.0f) {
        obj.anim = animation_t::none;
        obj.time = 0.0f;
        return;
      }

      obj.time -= t;
      obj.translation += (t * ctrl_direction);
    }

    void playSpline(float t, object_t &obj)
    {
      if (obj.time <= 0.0f) {
        obj.anim = animation_t::none;
        obj.time = 0.0f;
        return;
      }

      obj.time -= t;
      obj.translation += glm::catmullRom(glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.2f, 0.3f, 0.0f),
          glm::vec3(0.4f, -0.4f, 0.0f),
          glm::vec3(1.0f, 0.8f, 0.0f),
          1.0f - obj.time);
    }

    void playAnimation1(float t, object_t &obj)
    {
      if (obj.time <= 0.0f) {
        obj.anim = animation_t::none;
        obj.time = 0.0f;
        return;
      }

      obj.time -= t;

      if (obj.time > .75f) {
        // spline
        obj.translation += glm::catmullRom(glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.3f, 0.3f, 0.0f),
          glm::vec3(0.4f, -0.4f, 0.0f),
          glm::vec3(1.0f, -0.8f, 0.0f),
          1.0f - obj.time);
      } else if (obj.time > .5f) {
        // rotate
        obj.rotation += glm::quat(1.0f, 0.0f, 0.0f, 0.0f) * (OFFSET_ROT * t);
      } else if (obj.time > .375f) {
        // scale up
        obj.scale += glm::vec3(1.0f, 1.0f, 1.0f) * (t * 0.5f);
      } else if (obj.time > .25f) {
        // scale down
        obj.scale -= glm::vec3(1.0f, 1.0f, 1.0f) * (t * 0.5f);
      } else {
        // linear back
        obj.translation += ((-10.0f * t) * glm::vec3(1.0f, 0.0f, 0.0f));
      }
    }

    void renderObjects(Shader sh, float deltaTime)
    {
      for (object_t &obj : this->vobj) {
        // animation
        if (obj.anim != animation_t::none) {
          switch(obj.anim){
            case animation_t::linear:
              this->playLinear(deltaTime, glm::vec3(1.0f, 1.0f, 0.0f), obj); break;
            case animation_t::spline:
              this->playSpline(deltaTime, obj); break;
            case animation_t::animation1:
              this->playAnimation1(deltaTime, obj); break;
            case animation_t::rotate_pt:
              this->playRotation(deltaTime, glm::vec3(4.0f, 0.0f, 0.0f), obj); break;
            default:
              std::cout << "Nothing to do for animation " << obj.anim << std::endl;
              break;
          }
        }

        obj.mmod = glm::translate(obj.mmod, obj.translation);
        obj.mmod = glm::rotate(obj.mmod, obj.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        obj.mmod = glm::rotate(obj.mmod, obj.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        obj.mmod = glm::rotate(obj.mmod, obj.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        obj.mmod = glm::scale(obj.mmod, obj.scale);

        // TODO remove
        //std::cout << "Translation " << std::endl;
        //print_vec(obj.translation);
        //std::cout << "Position ? " << std::endl;
        //print_vec(glm::vec3(obj.mmod[3]));
        //std::cout << "rotation " << std::endl;
        //print_quat(obj.rotation);
        //std::cout << "scale " << std::endl;
        //print_vec(obj.scale);
        //std::cout << "============" << std::endl;
        //system("clear");

        //= render =
        sh.setMat4("model", obj.mmod);
        this->Draw(sh);
        obj.mmod = glm::mat4(1.0f);
      }
    }

    object_t & getObj()
    { return this->vobj[this->slc_obj]; }

    void selectObj(int n)
    {
      this->slc_obj = (n < 0 || n > static_cast<int>(this->vobj.size() -1)) ? this->slc_obj : n;
    }

    void setValue(animation_t an, float time)
    {
      this->vobj[this->slc_obj].anim = an;
      this->vobj[this->slc_obj].time = time;
    }

  private:
    /* attributes */
    unsigned slc_obj = 0;
    vector<object_t> vobj;

    /*  Functions   */
    // draws the model, and thus all its meshes
    void Draw(Shader shader)
    {
      for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
    }

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path)
    {
      // read file via ASSIMP
      Assimp::Importer importer;
      const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
      // check for errors
      if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
      {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
      }
      // retrieve the directory path of the filepath
      directory = path.substr(0, path.find_last_of('/'));

      // process ASSIMP's root node recursively
      processNode(scene->mRootNode, scene);
    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene)
    {
      // process each mesh located at the current node
      for(unsigned int i = 0; i < node->mNumMeshes; i++)
      {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
      }
      // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
      for(unsigned int i = 0; i < node->mNumChildren; i++)
      {
        processNode(node->mChildren[i], scene);
      }

    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
      // data to fill
      vector<Vertex> vertices;
      vector<unsigned int> indices;
      vector<Texture> textures;

      // Walk through each of the mesh's vertices
      for(unsigned int i = 0; i < mesh->mNumVertices; i++)
      {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
          glm::vec2 vec;
          // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
          // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
          vec.x = mesh->mTextureCoords[0][i].x; 
          vec.y = mesh->mTextureCoords[0][i].y;
          vertex.TexCoords = vec;
        }
        else
          vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
      }
      // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
      for(unsigned int i = 0; i < mesh->mNumFaces; i++)
      {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
          indices.push_back(face.mIndices[j]);
      }
      // process materials
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
      // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
      // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
      // Same applies to other texture as the following list summarizes:
      // diffuse: texture_diffuseN
      // specular: texture_specularN
      // normal: texture_normalN

      // 1. diffuse maps
      vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      // 2. specular maps
      vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
      // 3. normal maps
      std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
      textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
      // 4. height maps
      std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
      textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

      // return a mesh object created from the extracted mesh data
      return Mesh(vertices, indices, textures);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
    {
      vector<Texture> textures;
      for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
      {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
          if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
          {
            textures.push_back(textures_loaded[j]);
            skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
            break;
          }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
          Texture texture;
          texture.id = TextureFromFile(str.C_Str(), this->directory);
          texture.type = typeName;
          texture.path = str.C_Str();
          textures.push_back(texture);
          textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
      }
      return textures;
    }
};


unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}
#endif
