#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class BitmapStore {
private:
  map<string, Texture> m_BitmapsMap;
  static BitmapStore* m_s_Instance;

public:
  BitmapStore();
  static sf::Texture& getBitmap(string const& filename);
  static void addBitmap(string const& filename);
};
