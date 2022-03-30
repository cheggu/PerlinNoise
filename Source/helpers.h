#pragma once
#include "includes.h"

siv::PerlinNoise::seed_type seed = 231232984012;

siv::PerlinNoise perlin{ seed };

sf::Sprite generatePerlin(sf::Texture& texture, double octaves, double persistance) {
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

            noise = perlin.octave2D_01((x / 1000.0), (z / 1000.0), octaves, persistance);
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

    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);

    return sprite;
}

int random(int start, int fin) {
    return rand() % fin + start;
}
