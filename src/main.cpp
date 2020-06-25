#include <iostream>

#include "Loader.hpp"
#include "LoaderModels.hpp"

int main(int argc, char const *argv[])
{
  Loader *ldr = new Loader("test.teldr");
  std::cout << "\nprinting files";
  std::cout << "\nTextures:\n";
  if (ldr->flags < 0)
  {
    std::cout << "An error occured while reading file";
  }
  else
  {
    for (auto &i : ldr->getTexture())
    {
      std::cout << i->handle << " ";
      std::cout << i->path;
      std::cout << "\n";
    }
    std::cout << "\nAnimations:\n";
    for (auto &i : ldr->getAnimation())
    {
      std::cout << i->handle << " ";
      std::cout << i->texHandle;
      std::cout << "\n";
      for (auto &j : i->frames)
      {
        std::cout << j->top << " ";
        std::cout << j->left << " ";
        std::cout << j->width << " ";
        std::cout << j->height << " ";
        std::cout << "\n";
      }
      std::cout << "\n";
    }
    std::cout << "\nLoaders:\n";
    for (auto &i : ldr->getLoader())
    {
      std::cout << i->handle << " ";
      std::cout << i->path;
      std::cout << "\n";
    }
  }
  // Loader *ldr = new Loader();
  // AnimationModel *anim = new AnimationModel();
  // anim->handle = 5;
  // anim->texHandle = 3;
  // anim->frames.push_back(new sf::IntRect(1, 1, 1, 1));
  // anim->frames.push_back(new sf::IntRect(2, 2, 2, 2));
  // anim->frames.push_back(new sf::IntRect(3, 3, 3, 3));
  // anim->frames.push_back(new sf::IntRect(4, 4, 4, 4));
  // ldr->addAnimation(anim);
  // TextureModel *tex = new TextureModel();
  // tex->handle = 9;
  // tex->path = "AAAAA";
  // ldr->addTexture(tex);
  // tex = new TextureModel();
  // tex->path = "BBBB";
  // tex->handle = 1;
  // ldr->addTexture(tex);
  // tex = new TextureModel();
  // tex->path = "AAAAA";
  // tex->handle = 2;
  // ldr->addTexture(tex);
  // ldr->saveToFile("test");

  return 0;
}
