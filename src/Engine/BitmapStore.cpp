#include "BitmapStore.h"
#include <cassert>

BitmapStore* BitmapStore::m_s_Instance = nullptr;

BitmapStore::BitmapStore() {
  assert(m_s_Instance == nullptr);
  m_s_Instance = this;
}

void BitmapStore::addBitmap(const string &filename) {
  map<string, Texture> & bitmapsMap = m_s_Instance->m_BitmapsMap;
  auto keyValuePair = bitmapsMap.find(filename);
  if (keyValuePair == bitmapsMap.end()) {
    Texture& texture = bitmapsMap[filename];
    texture.loadFromFile(filename);
  }
}

Texture& BitmapStore::getBitmap(const string &filename) {
  map<string, Texture> & bitmapsMap = m_s_Instance->m_BitmapsMap;
  auto keyValuePair = bitmapsMap.find(filename);
  if (keyValuePair != bitmapsMap.end()) {
    return keyValuePair->second;
  }
  else {
    #ifdef debuggingConsole
      cout << "BitmapStore::getBitmap()Texture not found Crrrashh!" << endl;
    #endif
    return keyValuePair->second;
  }
}
