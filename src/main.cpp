#define GLEW_STATIC

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include "App.hpp"

int main() {
    RenderContext context;

    Window window(context, WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Renderer");

    App app(window);

    app.run();  

    return 0;
}

