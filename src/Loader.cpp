
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

#include "Loader.hpp"

Loader::Loader()
{
}

Loader::Loader(const char *file_path)
{
  loadFromFile(file_path);
}
Loader::~Loader()
{
  textures.clear();
  animations.clear();
  loaders.clear();
}

bool Loader::loadFromFile(const char *file_path)
{
  // TODO : parse file to objects
  std::ifstream ifile;
  ifile.open(file_path, std::ifstream::in | std::ifstream::binary);
  if (!ifile.is_open())
  {
    return false;
  }
  std::size_t count;
  std::cout << "hello ";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  std::cout << count << "\n";
  for (std::size_t i = 0; i < count; i++)
  {
    std::size_t size;
    TextureModel *texture = new TextureModel();
    // std::cout << sizeof texture;
    ifile.read(reinterpret_cast<char *>(&(texture->handle)), sizeof texture->handle);
    ifile.read(reinterpret_cast<char *>(&size), sizeof(size));
    texture->path.resize(size);
    ifile.read(&(texture->path[0]), size);
    textures.push_back(texture);
  }
  std::cout << textures.size();
  ifile.close();
  return true;
}
bool Loader::saveToFile(const char *file_path)
{
  std::ofstream ofile;
  std::string actual_file_path = file_path;
  std::string temp_file_path = file_path;
  temp_file_path += ".tmp";
  ofile.open(temp_file_path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
  if (!ofile.is_open())
  {
    return false;
  }
  std::size_t size = textures.size();
  std::cout << size;
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  std::cout << "hello";
  for (auto &texture : textures)
  {
    std::size_t size = texture->path.length();
    ofile.write(reinterpret_cast<char *>(&(texture->handle)), sizeof texture->handle);
    ofile.write(reinterpret_cast<char *>(&size), sizeof size);
    ofile << texture->path;
  }
  ofile.close();
  return true;
}

bool Loader::addTexture(TextureModel *textureModel)
{
  bool exist = false;
  for (auto &texture : textures)
  {
    if (texture->handle == textureModel->handle)
    {
      exist = true;
      break;
    }
  }
  if (!exist)
  {
    textures.push_back(textureModel);
  }
  return !exist;
}
bool Loader::addAnimation(AnimationModel *animationModel)
{
  bool exist = false;
  for (auto &animation : animations)
  {
    if (animation->handle == animationModel->handle)
    {
      exist = true;
      break;
    }
  }
  if (!exist)
  {
    animations.push_back(animationModel);
  }
  return !exist;
}
bool Loader::addLoader(LoaderModel *loaderModel)
{
  bool exist = false;
  for (auto &loader : loaders)
  {
    if (loader->handle == loaderModel->handle)
    {
      exist = true;
      break;
    }
  }
  if (!exist)
  {
    loaders.push_back(loaderModel);
  }
  return !exist;
}

const std::vector<TextureModel *> &Loader::getTexture()
{
  return textures;
}
const std::vector<AnimationModel *> &Loader::getAnimation()
{
  return animations;
}
const std::vector<LoaderModel *> &Loader::getLoader()
{
  return loaders;
}

bool Loader::removeTexture(const int handle)
{
  const std::size_t len = textures.size();
  textures.erase(std::remove_if(textures.begin(), textures.end(), [&handle](TextureModel *texture) { return texture->handle == handle; }), textures.end());
  return textures.size() < len;
}
bool Loader::removeAnimation(const int handle)
{
  const std::size_t len = animations.size();
  animations.erase(std::remove_if(animations.begin(), animations.end(), [&handle](AnimationModel *animation) { return animation->handle == handle; }), animations.end());
  return animations.size() < len;
}
bool Loader::removeLoader(const int handle)
{
  const std::size_t len = loaders.size();
  loaders.erase(std::remove_if(loaders.begin(), loaders.end(), [&handle](LoaderModel *loader) { return loader->handle == handle; }), loaders.end());
  return loaders.size() < len;
}