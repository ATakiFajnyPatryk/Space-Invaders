#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button {
private:
  RectangleShape m_Button;
  Text m_ButtonText;
  Font m_Font;

public:
  string m_Text;
  FloatRect m_Collider;

  Button(Vector2f position, float width, float height, int red, int green,
         int blue, const string& text);
  void draw(RenderWindow& window);
};
