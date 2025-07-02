# GraphicsEngineOpenGL

**GraphicsEngineOpenGL** to prosty silnik graficzny oparty na OpenGL, zaprojektowany do nauki i eksperymentowania z nowoczesnymi technikami renderingu. Projekt oferuje modularną strukturę, wsparcie dla ładowania modeli 3D oraz system oświetlenia z cieniowaniem.

## ✨ Funkcje

- 🔻 **Ładowanie modeli 3D z plików** (OBJ, FBX, itd.) za pomocą biblioteki [Assimp](https://github.com/assimp/assimp).
- 💡 **System oświetlenia**:
  - światło kierunkowe, punktowe i reflektory (spotlights),
  - obsługa ambient, diffuse i specular lighting.
- 🧪 **Shading**:
  - własne shadery GLSL,
  - obsługa materiałów i tekstur.
- 🔧 **Encapsulacja logiki**:
  - modularna struktura: `App`, `Shader`, `Light`, `Mesh`, `Renderable`, itd.
  - łatwe rozszerzanie i zarządzanie sceną.
- 🌌 **Skybox** oraz obsługa cieniowania (shadow mapping) — w przygotowaniu lub częściowo zaimplementowane.
- 🎮 Sterowanie kamerą w stylu FPS (WASD + mysz).

## 🔧 Wymagania

- C++17
- OpenGL 3.3+
- GLEW
- GLFW
- Assimp
- GLM
- stb_image
- SOIL

## 🚀 Jak uruchomić

1. Skonfiguruj projekt w środowisku wspierającym CMake (najlepiej Visual Studio).
2. Upewnij się, że biblioteki są poprawnie dołączone.
3. Zbuduj projekt.
4. Uruchom i eksploruj scenę 3D

## 🗂 Struktura

- `App.hpp/cpp` – główna pętla aplikacji, renderowanie, zarządzanie sceną.
- `Shader.hpp` – ładowanie i zarządzanie shaderami GLSL.
- `Renderable`, `RenderableObject`, `Mesh` – komponenty renderowalne i obsługa modeli.
- `Camera.hpp` – funkcje kamery i podstawoe definicje.
- `Window.hpp` – zarządzanie oknem i kamerą.

## 📸 Screenshot (opcjonalnie)
![Silnik w akcji](gifs/gif2.gif)
![Silnik w akcji](gifs/gif1.gif)

## 📃 Licencja

Projekt edukacyjny – do dowolnego użytku. 🚀
