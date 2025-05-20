#include <SFML/Graphics.hpp>

using namespace sf;

int main(int argc, char *argv[]) {
    RenderWindow window(VideoMode(500, 500), "Dispatcher", Style::Titlebar | Style::Close);

    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();


        window.display();
    }

    return 0;
}
