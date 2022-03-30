#include "includes.h"
#include "PerlinNoise.hpp"

siv::PerlinNoise::seed_type seed = 231232984012;

siv::PerlinNoise perlin{ seed };

sf::Sprite drawPerlin(sf::Texture& texture, double octaves, double persistance) {
    double x = 0;
    double y = 42;
    double z = 0;
    double noise;
    double a;
    sf::Color color;

    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Red);

    double xLim = WIDTH;
    double yLim = HEIGHT;
    
    for (x = 0; x < xLim; x++) {
        for (z = 0; z < yLim; z++) {
            
            noise = perlin.octave2D_01((x / 1000.0), (z / 1000.0 ), octaves, persistance);
            if (noise < 0.35) {
                noise = 0.0;
            }
            else if (noise >= 0.35 && noise < 0.45) {
                noise = 0.2;
            }
            else if (noise >= 0.45 && noise < 0.55) {
                noise = 0.4;
            }
            else if (noise >= 0.55 && noise < 0.65) {
                noise = 0.6;
            }
            else if (noise >= 0.65 && noise < 0.75) {
                noise = 0.8;
            }
            else if (noise > 0.75) {
                noise = 1;
            }
            
            a = (noise) * 255;
            color = sf::Color(255, 255, 255, a);
            image.setPixel(x, z, color);
        }
    }

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your 
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);
    //Then, in PlayState::render()
    return sprite;

}

int main() {

    sf::Texture texture;

    sf::Sprite perlinSprite = drawPerlin(texture, 9, 1);

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
                        + "\nSeed: " + std::to_string(seed));

        sf::Event event; 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            seed = random(0, 999999999);
            perlin.reseed(seed);
            perlinSprite = drawPerlin(texture, 1, 3);
        }
        
        window.draw(perlinSprite);
        window.draw(time);
        window.display();
    }

    return 0;
}