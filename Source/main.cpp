#include "includes.h"
#include "PerlinNoise.hpp"
#include "helpers.h"

int main() {

    double octaves = 9, percistance = 1, step = 0.1;

    sf::Texture texture;

    sf::Sprite perlinSprite = generatePerlin(texture, octaves, percistance);

    srand(std::time(0));
    float dt;
    sf::Clock dt_clock;

    sf::Clock timer;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    sf::Text time;
    time.setFont(font);
    time.setString("Elapsed: " + std::to_string(timer.getElapsedTime().asSeconds()));
    time.setCharacterSize(16); // in pixels, not points!
    time.setFillColor(sf::Color::Red);
    time.setPosition(10, 10);
    time.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (window.isOpen()) {
        window.clear();

        time.setString("Elapsed: " + std::to_string(timer.getElapsedTime().asSeconds())
                        + "\nSeed: " + std::to_string(seed)
                        + "\nOctaves (-A\tD+): " + std::to_string(octaves)
                        + "\nPercistance/Amplitude (-Z\tC+): " + std::to_string(percistance)
                        + "\nStep (-(-)\t(=)+): " + std::to_string(step));

        sf::Event event; 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
            step += 0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen)) {
            step -= 0.001;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            seed = random(0, 9999999);
            perlin.reseed(seed);
            perlinSprite = generatePerlin(texture, octaves, percistance);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            octaves -= step;
            perlinSprite = generatePerlin(texture, octaves, percistance);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            octaves += step;
            perlinSprite = generatePerlin(texture, octaves, percistance);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            percistance -= step;
            perlinSprite = generatePerlin(texture, octaves, percistance);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            percistance += step;
            perlinSprite = generatePerlin(texture, octaves, percistance);
        }

        window.draw(perlinSprite);
        window.draw(time);
        window.display();
    }

    return 0;
}