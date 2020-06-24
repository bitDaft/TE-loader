

#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>

#include "LoaderModels.hpp"

class Loader
{
public:
  Loader();
  Loader(const char *);
  ~Loader();

  void loadFile(const char *);

  int addTexture(TextureModel &);
  int addAnimation(AnimationModel &);
  int addLoader(LoaderModel &);

  void removeTexture(int);
  void removeAnimation(int);
  void removeLoader(int);

private:
  std::vector<TextureModel> textures;
  std::vector<AnimationModel> animations;
  std::vector<LoaderModel> loaders;
}

#endif