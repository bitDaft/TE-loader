
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

  textures.clear();
  animations.clear();
  loaders.clear();

  std::size_t count;
  // TEXTURES
  std::cout << "\nLoading Textures";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  textures.reserve(count);
  for (std::size_t i = 0; i < count; i++)
  {
    std::size_t length;
    TextureModel *texture = new TextureModel();
    ifile.read(reinterpret_cast<char *>(&(texture->handle)), sizeof texture->handle);
    ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
    texture->path.resize(length);
    ifile.read(&(texture->path[0]), length);
    textures.push_back(texture);
  }
  std::cout << "\nDone Textures";

  // ANIMATIONS
  std::cout << "\nLoading Animations";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  animations.reserve(count);
  for (std::size_t i = 0; i < count; i++)
  {
    std::size_t length;
    AnimationModel *animation = new AnimationModel();
    ifile.read(reinterpret_cast<char *>(&(animation->handle)), sizeof animation->handle);
    ifile.read(reinterpret_cast<char *>(&(animation->texHandle)), sizeof animation->texHandle);
    ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
    animation->frames.reserve(length);
    for (size_t j = 0; j < length; j++)
    {
      int left, top, width, height;
      ifile.read(reinterpret_cast<char *>(&left), sizeof left);
      ifile.read(reinterpret_cast<char *>(&top), sizeof top);
      ifile.read(reinterpret_cast<char *>(&width), sizeof width);
      ifile.read(reinterpret_cast<char *>(&height), sizeof height);
      animation->frames.push_back(new sf::IntRect(left, top, width, height));
    }
    animations.push_back(animation);
  }
  std::cout << "\nDone Animations";

  // LOADERS
  std::cout << "\nLoading Loaders";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  loaders.reserve(count);
  for (std::size_t i = 0; i < count; i++)
  {
    std::size_t length;
    LoaderModel *loader = new LoaderModel();
    ifile.read(reinterpret_cast<char *>(&(loader->handle)), sizeof loader->handle);
    ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
    loader->path.resize(length);
    ifile.read(&(loader->path[0]), length);
    loaders.push_back(loader);
  }
  std::cout << "\nDone Loaders";

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

  std::size_t size;
  // TEXTURES
  std::cout << "\nWriting Textures";
  size = textures.size();
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  for (auto &texture : textures)
  {
    ofile.write(reinterpret_cast<char *>(&(texture->handle)), sizeof texture->handle);
    std::size_t length = texture->path.length();
    ofile.write(reinterpret_cast<char *>(&length), sizeof length);
    ofile << texture->path;
  }
  std::cout << "\nDone Textures";

  // ANIMATIONS
  std::cout << "\nWriting Animations";
  size = animations.size();
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  for (auto &animation : animations)
  {
    ofile.write(reinterpret_cast<char *>(&(animation->handle)), sizeof animation->handle);
    ofile.write(reinterpret_cast<char *>(&(animation->texHandle)), sizeof animation->texHandle);
    std::size_t length = animation->frames.size();
    ofile.write(reinterpret_cast<char *>(&length), sizeof length);
    for (auto &frame : animation->frames)
    {
      ofile.write(reinterpret_cast<char *>(&frame->left), sizeof frame->left);
      ofile.write(reinterpret_cast<char *>(&frame->top), sizeof frame->top);
      ofile.write(reinterpret_cast<char *>(&frame->width), sizeof frame->width);
      ofile.write(reinterpret_cast<char *>(&frame->height), sizeof frame->height);
    }
  }
  std::cout << "\nDone Animations";

  // LOADERS
  std::cout << "\nWriting Loaders";
  size = loaders.size();
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  for (auto &loader : loaders)
  {
    ofile.write(reinterpret_cast<char *>(&(loader->handle)), sizeof loader->handle);
    std::size_t length = loader->path.length();
    ofile.write(reinterpret_cast<char *>(&length), sizeof length);
    ofile << loader->path;
  }
  std::cout << "\nDone Loaders";

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