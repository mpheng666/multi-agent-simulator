#include <SFML/Graphics.hpp>

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(400, 400), "Mutli-Agent-Simulator",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; // for showing

    sf::Texture t;
    sf::Texture black_square_texture;
    black_square_texture.loadFromFile("../images/black_with_white_corners.png");
    // t.loadFromFile("../images/poly_light_blue.png");
    t.loadFromFile("../images/tiles.jpg");
    sf::Sprite s(t);
    sf::Sprite black_square_sprite(black_square_texture);

    sf::Vector2u black_square_size = black_square_texture.getSize();
    // black_square_texture.

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)
                grid[i][j] = 9;
            else
                grid[i][j] = 0;
        }
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            int n = 0;
            if (grid[i][j] == 9)
                continue;
            if (grid[i + 1][j] == 9)
                n++;
            if (grid[i][j + 1] == 9)
                n++;
            if (grid[i - 1][j] == 9)
                n++;
            if (grid[i][j - 1] == 9)
                n++;
            if (grid[i + 1][j + 1] == 9)
                n++;
            if (grid[i - 1][j - 1] == 9)
                n++;
            if (grid[i - 1][j + 1] == 9)
                n++;
            if (grid[i + 1][j - 1] == 9)
                n++;
            grid[i][j] = n;
        }
    }

    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // if (event.key.code == sf::Mouse::Left)
                //     sgrid[x][y] = grid[x][y];
                // else if (event.key.code == sf::Mouse::Right)
                //     sgrid[x][y] = 11;
            }
        }
        
        window.clear(sf::Color::Black);

        for (int i = 1; i <= 10; i++) {

            for (int j = 1; j <= 10; j++) {
                if (sgrid[x][y] == 9)
                {
                    sgrid[i][j] = grid[i][j];
                }
                s.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
                black_square_sprite.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                black_square_sprite.setTextureRect(
                        sf::IntRect(sgrid[3][5] * w, 0, w, w));

                window.draw(s);
                window.draw(black_square_sprite);
            }
        }
        window.display();
    }

    return 0;
}