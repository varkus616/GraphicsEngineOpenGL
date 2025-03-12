#define GLEW_STATIC

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include "App.hpp"

int main() {
    RenderContext context;

    Window window(context, WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Renderer");

    App app(window);

    app.run();  

    return 0;
}

