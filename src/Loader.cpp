
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

#include "Loader.hpp"

int constant = 0x10AD;

Loader::Loader()
    : flags(0)
{
}

Loader::Loader(const char *file_path)
    : flags(0)
{
  loadFromFile(file_path);
}
Loader::~Loader()
{
  flags = 0;
  clearData();
}

void Loader::clearData()
{
  for (auto &i : textures)
  {
    delete i;
  }
  for (auto &i : animations)
  {
    for (auto &j : i->frames)
      delete j;
    delete i;
  }
  for (auto &i : loaders)
  {
    delete i;
  }
  textures.clear();
  animations.clear();
  loaders.clear();
}

bool Loader::loadFromFile(const char *file_path)
{
  std::ifstream ifile;
  ifile.open(file_path, std::ifstream::in | std::ifstream::binary);
  if (!ifile.is_open())
  {
    ifile.close();
    flags = -1;
    return false;
  }

  int file_constant = 0;
  ifile.read(reinterpret_cast<char *>(&file_constant), sizeof file_constant);
  if (file_constant != constant)
  {
    flags = -2;
    return false;
  }

  clearData();
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

  // TILESETS
  std::cout << "\nLoading Tilesets";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  tilesets.reserve(count);
  for (std::size_t i = 0; i < count; i++)
  {
    TilesetModel *tileset = new TilesetModel();
    ifile.read(reinterpret_cast<char *>(&(tileset->handle)), sizeof tileset->handle);
    ifile.read(reinterpret_cast<char *>(&(tileset->texHandle)), sizeof tileset->texHandle);
    ifile.read(reinterpret_cast<char *>(&(tileset->regionBased)), sizeof tileset->regionBased);
    if (tileset->regionBased)
    {
      int left, top, width, height;
      int tilex, tiley;
      ifile.read(reinterpret_cast<char *>(&left), sizeof left);
      ifile.read(reinterpret_cast<char *>(&top), sizeof top);
      ifile.read(reinterpret_cast<char *>(&width), sizeof width);
      ifile.read(reinterpret_cast<char *>(&height), sizeof height);
      tileset->region = sf::IntRect(left, top, width, height);
      ifile.read(reinterpret_cast<char *>(&tilex), sizeof tilex);
      ifile.read(reinterpret_cast<char *>(&tiley), sizeof tiley);
      tileset->tileSize = sf::Vector2i(tilex, tiley);
    }
    else
    {
      std::size_t length;
      ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
      tileset->tiles.reserve(length);
      for (size_t j = 0; j < length; j++)
      {
        int left, top, width, height;
        ifile.read(reinterpret_cast<char *>(&left), sizeof left);
        ifile.read(reinterpret_cast<char *>(&top), sizeof top);
        ifile.read(reinterpret_cast<char *>(&width), sizeof width);
        ifile.read(reinterpret_cast<char *>(&height), sizeof height);
        tileset->tiles.push_back(new sf::IntRect(left, top, width, height));
      }
    }
    tilesets.push_back(tileset);
  }
  std::cout << "\nDone Tilesets";

  // ANIMATIONS
  std::cout << "\nLoading Animations";
  ifile.read(reinterpret_cast<char *>(&count), sizeof count);
  animations.reserve(count);
  for (std::size_t i = 0; i < count; i++)
  {
    AnimationModel *animation = new AnimationModel();
    ifile.read(reinterpret_cast<char *>(&(animation->handle)), sizeof animation->handle);
    ifile.read(reinterpret_cast<char *>(&(animation->texHandle)), sizeof animation->texHandle);
    ifile.read(reinterpret_cast<char *>(&(animation->tileBased)), sizeof animation->tileBased);
    if (animation->tileBased)
    {
      ifile.read(reinterpret_cast<char *>(&(animation->tilesetHandle)), sizeof animation->tilesetHandle);
      std::size_t length;
      ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
      for (std::size_t j = 0; j < length; j++)
      {
        int tileid;
        ifile.read(reinterpret_cast<char *>(&tileid), sizeof(tileid));
        animation->tileids.push_back(tileid);
      }
    }
    else
    {
      std::size_t length;
      ifile.read(reinterpret_cast<char *>(&length), sizeof(length));
      animation->frames.reserve(length);
      for (std::size_t j = 0; j < length; j++)
      {
        int left, top, width, height;
        ifile.read(reinterpret_cast<char *>(&left), sizeof left);
        ifile.read(reinterpret_cast<char *>(&top), sizeof top);
        ifile.read(reinterpret_cast<char *>(&width), sizeof width);
        ifile.read(reinterpret_cast<char *>(&height), sizeof height);
        animation->frames.push_back(new sf::IntRect(left, top, width, height));
      }
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
  actual_file_path += ".teldr";
  std::string temp_file_path = file_path;
  temp_file_path += ".tmp";
  ofile.open(temp_file_path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
  if (!ofile.is_open())
  {
    std::remove(temp_file_path.c_str());
    ofile.close();
    flags = -1;
    return false;
  }
  ofile.write(reinterpret_cast<char *>(&constant), sizeof constant);

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

  // TILESETS
  std::cout << "\nWriting Tilesets";
  size = tilesets.size();
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  for (auto &tileset : tilesets)
  {
    ofile.write(reinterpret_cast<char *>(&(tileset->handle)), sizeof tileset->handle);
    ofile.write(reinterpret_cast<char *>(&(tileset->texHandle)), sizeof tileset->texHandle);
    ofile.write(reinterpret_cast<char *>(&(tileset->regionBased)), sizeof tileset->regionBased);
    if (tileset->regionBased)
    {
      ofile.write(reinterpret_cast<char *>(&tileset->region.left), sizeof tileset->region.left);
      ofile.write(reinterpret_cast<char *>(&tileset->region.top), sizeof tileset->region.top);
      ofile.write(reinterpret_cast<char *>(&tileset->region.width), sizeof tileset->region.width);
      ofile.write(reinterpret_cast<char *>(&tileset->region.height), sizeof tileset->region.height);
      ofile.write(reinterpret_cast<char *>(&tileset->tileSize.x), sizeof tileset->tileSize.x);
      ofile.write(reinterpret_cast<char *>(&tileset->tileSize.y), sizeof tileset->tileSize.y);
    }
    else
    {
      std::size_t length = tileset->tiles.size();
      ofile.write(reinterpret_cast<char *>(&length), sizeof length);
      for (auto &tile : tileset->tiles)
      {
        ofile.write(reinterpret_cast<char *>(&tile->left), sizeof tile->left);
        ofile.write(reinterpret_cast<char *>(&tile->top), sizeof tile->top);
        ofile.write(reinterpret_cast<char *>(&tile->width), sizeof tile->width);
        ofile.write(reinterpret_cast<char *>(&tile->height), sizeof tile->height);
      }
    }
  }
  std::cout << "\nDone Tilesets";

  // ANIMATIONS
  std::cout << "\nWriting Animations";
  size = animations.size();
  ofile.write(reinterpret_cast<char *>(&size), sizeof size);
  for (auto &animation : animations)
  {
    ofile.write(reinterpret_cast<char *>(&(animation->handle)), sizeof animation->handle);
    ofile.write(reinterpret_cast<char *>(&(animation->texHandle)), sizeof animation->texHandle);
    ofile.write(reinterpret_cast<char *>(&(animation->tileBased)), sizeof animation->tileBased);
    if (animation->tileBased)
    {

      ofile.write(reinterpret_cast<char *>(&(animation->tilesetHandle)), sizeof animation->tilesetHandle);
      std::size_t length = animation->tileids.size();
      ofile.write(reinterpret_cast<char *>(&length), sizeof length);
      for (auto &tileid : animation->tileids)
      {
        ofile.write(reinterpret_cast<char *>(&tileid), sizeof tileid);
      }
    }
    else
    {
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

  // copy from temp to actual file
  std::ifstream src(temp_file_path, std::ios::binary);
  std::ofstream dst(actual_file_path, std::ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();
  std::remove(temp_file_path.c_str());
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
bool Loader::addTileset(TilesetModel *tilesetModel)
{
  bool exist = false;
  for (auto &tileset : tilesets)
  {
    if (tileset->handle == tilesetModel->handle)
    {
      exist = true;
      break;
    }
  }
  if (!exist)
  {
    tilesets.push_back(tilesetModel);
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
const std::vector<TilesetModel *> &Loader::getTileset()
{
  return tilesets;
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
bool Loader::removeTileset(const int handle)
{
  const std::size_t len = tilesets.size();
  tilesets.erase(std::remove_if(tilesets.begin(), tilesets.end(), [&handle](TilesetModel *tileset) { return tileset->handle == handle; }), tilesets.end());
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