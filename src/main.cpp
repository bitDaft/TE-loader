#include <iostream>

#include "Loader.hpp"
#include "LoaderModels.hpp"

int main(int argc, char const *argv[])
{
  Loader *ldr = new Loader("basic.teldr");
  if (ldr->flags < 0)
  {
    std::cout << "An error occured while reading file";
  }
  else
  {
    std::cout << "\nprinting files\n";
    std::cout << "\nTextures:\n";
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
      std::cout << i->texHandle << " ";
      std::cout << i->tileBased;
      std::cout << "\n";
      if (i->tileBased)
      {
        for (auto &j : i->tileids)
        {
          std::cout << j << " ";
          std::cout << "\n";
        }
      }
      else
      {
        for (auto &j : i->frames)
        {
          std::cout << j->top << " ";
          std::cout << j->left << " ";
          std::cout << j->width << " ";
          std::cout << j->height << " ";
          std::cout << "\n";
        }
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
  // anim->handle = 1;
  // anim->texHandle = 1;
  // anim->tileBased = 0;
  // anim->frames.push_back(new sf::IntRect(32, 0, 32, 32));
  // anim->frames.push_back(new sf::IntRect(64, 0, 32, 32));
  // anim->frames.push_back(new sf::IntRect(32, 0, 32, 32));
  // anim->frames.push_back(new sf::IntRect(0, 0, 32, 32));
  // ldr->addAnimation(anim);
  // TextureModel *tex = new TextureModel();
  // tex->handle = 1;
  // tex->path = "./assets/sheet2.png";
  // ldr->addTexture(tex);
  // LoaderModel *loader = new LoaderModel();
  // loader->handle = 1;
  // loader->path = "./basic.teldr";
  // ldr->addLoader(loader);

  // ldr->saveToFile("basic");

  return 0;
}
