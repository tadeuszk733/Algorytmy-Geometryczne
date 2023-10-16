#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

class Visualizer
{
public:
    Visualizer();

    void load_file();

    sf::Font title_font;
    sf::Text title{};
    std::vector<std::function<void(sf::RenderWindow &)>> draw_sequence;

    sf::Text getTitle() const;

    void setTitle(const std::string &title);

    void onResize(const sf::RenderWindow &window);
};
