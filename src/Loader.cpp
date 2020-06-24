
#include <algorithm>

#include "Loader.hpp"

Loader::Loader()
{
}

Loader::Loader(const char *file_path)
{
  loadFile(file_path);
}
Loader::~Loader()
{
  textures.clear();
  animations.clear();
  loaders.clear();
}

void Loader::loadFile(const char *file_path)
{
  // TODO : parse file to objects
}

int Loader::AddTexture(TextureModel &textureModel)
{
  textures.push_back(textureModel);
}
int Loader::AddAnimation(AnimationModel &animationModel)
{
  animations.push_back(animationModel);
}
int Loader::AddLoader(LoaderModel &loaderModel)
{
  loaders.push_back(loaderModel);
}

void Loader::RemoveTexture(int handle)
{
  textures.erase(std::remove_if(textures.begin(), textures.end(), [&handle](int thisHandle) { return thisHandle == handle }), textures.end());
}
void Loader::RemoveAnimation(int handle)
{
  animations.erase(std::remove_if(animations.begin(), animations.end(), [&handle](int thisHandle) { return thisHandle == handle }), animations.end());
}
void Loader::RemoveLoader(int handle)
{
  loaders.erase(std::remove_if(loaders.begin(), loaders.end(), [&handle](int thisHandle) { return thisHandle == handle }), loaders.end());
}