#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include "Map.h"
#include "BugNav1.h"

int main(int argc, char** argv) {
    int width = 50;
    int height = 50;
    int cellSize = 12;

    // use --large for a map with 100,000 cells
    if (argc > 1 && std::string(argv[1]) == "--large") {
        width = 400;
        height = 250;
        cellSize = 2;
    }

    // use Map directly, including its smoothing pass
    Map generatedMap(32, width, height); 
    std::vector<std::vector<Tile>> tiles = generatedMap.getMap();

    // positions use {row, column}
    // (both endpoints are on the open border)
    std::pair<int, int> start = {height / 2, 0};
    std::pair<int, int> goal = {height / 2, width - 1};
    std::vector<std::pair<int, int>> path = {start};
    int step = 0;
    bool playing = false;
    bool calculated = false;
    sf::Clock timer;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(width * cellSize),
                                          static_cast<unsigned>(height * cellSize)}),
                            "BugNav: B calculate, P play/pause, N next, R reset",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // build the map picture once, w/ 1 image pixel per tile
    sf::Image image({static_cast<unsigned>(width), static_cast<unsigned>(height)}, sf::Color::White);
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            if (!tiles[row][column].isPassable()) {
                image.setPixel({static_cast<unsigned>(column), static_cast<unsigned>(row)}, sf::Color(65, 65, 65));
            }
        }
    }
    sf::Texture texture(image);
    sf::Sprite mapPicture(texture);
    mapPicture.setScale({static_cast<float>(cellSize), static_cast<float>(cellSize)});

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::B && !calculated) {
                    // this call runs the original algorithm before playback starts.
                    window.setTitle("BugNav: Calculating routes (see terminal logs)");
                    BugNav1 bug(tiles, start, goal);
                    path = bug.findPath();
                    if (path.empty()) path.push_back(start);
                    calculated = true;
                    std::string result = path.back() == goal ? "Goal reached" : "Goal not reached";
                    window.setTitle("BugNav: " + result + ". P play/pause, N next, R reset");
                    timer.restart();
                }
                if (key->code == sf::Keyboard::Key::P) {
                    playing = !playing;
                    timer.restart();
                }
                if (key->code == sf::Keyboard::Key::N) {
                    playing = false;
                    if (step + 1 < static_cast<int>(path.size())) step++;
                }
                if (key->code == sf::Keyboard::Key::R) {
                    step = 0;
                    playing = false;
                }
            }
        }

        // make playback faster when using --large
        bool largeMap = argc > 1 && std::string(argv[1]) == "--large";
        float secondsPerMove = largeMap ? 0.005f : 0.05f; // <-- ratio here makes movement x10 faster for --large

        if (playing && timer.getElapsedTime().asSeconds() >= secondsPerMove) {
            int moves = static_cast<int>(
                timer.getElapsedTime().asSeconds() / secondsPerMove);

            step = std::min(step + moves, static_cast<int>(path.size()) - 1);
            timer.restart();

            if (step + 1 >= static_cast<int>(path.size())) {
                playing = false;
            }
        }

        window.clear(sf::Color::White);
        window.draw(mapPicture);

        // draw the trail from the path returned by Bug1
        sf::VertexArray trail(sf::PrimitiveType::LineStrip);
        for (int i = 0; i <= step; i++) {
            sf::Vertex point;
            point.position = {(path[i].second + 0.5f) * cellSize,
                              (path[i].first + 0.5f) * cellSize};
            point.color = sf::Color::Blue;
            trail.append(point);
        }
        window.draw(trail);

        // draw start, goal, and the current robot position:
        std::pair<int, int> positions[] = {start, goal, path[step]};
        sf::Color colors[] = {sf::Color::Green, sf::Color(240, 190, 30), sf::Color::Blue};
        for (int i = 0; i < 3; i++) {
            float radius = std::max(2.f, cellSize * 0.3f);
            sf::CircleShape circle(radius);
            circle.setOrigin({radius, radius});
            circle.setPosition({(positions[i].second + 0.5f) * cellSize,
                                (positions[i].first + 0.5f) * cellSize});
            circle.setFillColor(colors[i]);
            window.draw(circle);
        }
        window.display();
    }
}
