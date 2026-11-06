#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include "Map.h"
#include "BugNav1.h"
#include "BugNav2.h"

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
    std::vector<std::pair<int, int>> paths[2] = {{start}, {start}};
    int steps[2] = {0, 0};
    sf::Color bugColors[2] = {sf::Color::Blue, sf::Color::Red};
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
                    window.setTitle("BugNav: Calculating both routes (see terminal logs)");
                    BugNav1 bug1(tiles, start, goal);
                    BugNav2 bug2(tiles, start, goal);
                    paths[0] = bug1.findPath();
                    paths[1] = bug2.findPath();
                    for (int i = 0; i < 2; i++) {
                        if (paths[i].empty() || paths[i].front() != start)
                            paths[i].insert(paths[i].begin(), start);
                        // stop at the first arrival, even if an algorithm keeps moving
                        auto arrival = std::find(paths[i].begin(), paths[i].end(), goal);
                        if (arrival != paths[i].end()) 
                            paths[i].erase(arrival + 1, paths[i].end());
                        steps[i] = 0;
                        std::cout << "Bug" << i + 1 << ": " << paths[i].size() - 1
                                  << " moves, " << (paths[i].back() == goal ? "goal reached" : "goal not reached")
                                  << std::endl;
                    }
                    playing = false;
                    calculated = true;
                    window.setTitle("BugNav: Bug1 blue, Bug2 red. P play/pause, N next, R reset");
                    timer.restart();
                }
                if (key->code == sf::Keyboard::Key::P && calculated) {
                    playing = !playing;
                    timer.restart();
                }
                if (key->code == sf::Keyboard::Key::N) {
                    playing = false;
                    for (int i = 0; i < 2; i++)
                        if (steps[i] + 1 < static_cast<int>(paths[i].size())) steps[i]++;
                }
                if (key->code == sf::Keyboard::Key::R) {
                    steps[0] = steps[1] = 0;
                    playing = false;
                }
            }
        }

        // make playback faster when using --large
        bool largeMap = argc > 1 && std::string(argv[1]) == "--large";
        float secondsPerMove = largeMap ? 0.005f : 0.05f; // <-- ratio here makes movement x10 faster for --large

        if (playing && timer.getElapsedTime().asSeconds() >= secondsPerMove) {
            int moves = static_cast<int>(timer.getElapsedTime().asSeconds() / secondsPerMove);

            for (int i = 0; i < 2; i++)
                steps[i] = std::min(steps[i] + moves, static_cast<int>(paths[i].size()) - 1);
            timer.restart();

            if (steps[0] + 1 >= static_cast<int>(paths[0].size()) &&
                steps[1] + 1 >= static_cast<int>(paths[1].size())) {
                playing = false;
            }
        }

        window.clear(sf::Color::White);
        window.draw(mapPicture);

        // draw both trails using the same playback clock:
        for (int bug = 0; bug < 2; bug++) {
            sf::VertexArray trail(sf::PrimitiveType::LineStrip);
            for (int i = 0; i <= steps[bug]; i++) {
                sf::Vertex point;
                point.position = {(paths[bug][i].second + 0.5f) * cellSize,
                                  (paths[bug][i].first + 0.5f) * cellSize};
                point.color = bugColors[bug];
                trail.append(point);
            }
            window.draw(trail);
        }

        // draw start, goal, and the current robot position:
        std::pair<int, int> positions[] = {start, goal, paths[0][steps[0]], paths[1][steps[1]]};
        sf::Color colors[] = {sf::Color::Green, sf::Color(240, 190, 30), bugColors[0], bugColors[1]};
        for (int i = 0; i < 4; i++) {
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
