#include <iostream>

#include "Loader.hpp"
#include "LoaderModels.hpp"

int main(int argc, char const *argv[])
{
  // Loader *ldr = new Loader("test.tmp");
  // std::cout << "\nprinting files\n";
  // for (auto &i : ldr->getTexture())
  // {
  //   std::cout << i->handle << " ";
  //   std::cout << i->path;
  //   std::cout << "\n";
  // }
  Loader *ldr = new Loader();
  AnimationModel *anim = new AnimationModel();
  anim->handle = 5;
  anim->texHandle = 3;
  anim->frames.push_back(new sf::IntRect(1, 1, 1, 1));
  anim->frames.push_back(new sf::IntRect(2, 2, 2, 2));
  anim->frames.push_back(new sf::IntRect(3, 3, 3, 3));
  anim->frames.push_back(new sf::IntRect(4, 4, 4, 4));
  ldr->addAnimation(anim);
  TextureModel *tex = new TextureModel();
  tex->handle = 9;
  tex->path = "AAAAA";
  ldr->addTexture(tex);
  tex = new TextureModel();
  tex->path = "BBBB";
  tex->handle = 1;
  ldr->addTexture(tex);
  // tex = new TextureModel();
  // tex->path = "AAAAA";
  // tex->handle = 2;
  // ldr->addTexture(tex);
  ldr->saveToFile("test");
  // std::cout << "\n";
  // for (auto &i : ldr->getTexture())
  // {
  //   std::cout << i->handle << " ";
  //   std::cout << i->path;
  //   std::cout << "\n";
  // }
  // delete tex;

  // std::cout << ldr->getTexture().size();

  return 0;
}
