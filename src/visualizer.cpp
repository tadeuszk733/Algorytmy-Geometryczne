#include "visualizer.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void drawGrid(sf::RenderWindow &win, int rows, int cols)
{
    // initialize values
    int numLines = rows + cols - 2;
    sf::VertexArray grid(sf::Lines, 2 * (numLines));
    win.setView(win.getDefaultView());
    auto size = win.getView().getSize();
    float rowH = size.y / rows;
    float colW = size.x / cols;
    // row separators
    for (int i = 0; i < rows - 1; i++) {
        int r = i + 1;
        float rowY = rowH * r;
        grid[i * 2].position = {0, rowY};
        grid[i * 2 + 1].position = {size.x, rowY};
    }
    // column separators
    for (int i = rows - 1; i < numLines; i++) {
        int c = i - rows + 2;
        float colX = colW * c;
        grid[i * 2].position = {colX, 0};
        grid[i * 2 + 1].position = {colX, size.y};
    }
    // draw it
    win.draw(grid);
}

void to_json(json &j, const sf::Vector2f &v)
{
    j = json{{"x", v.x}, {"y", v.y}};
}

void from_json(const json &j, sf::Vector2f &v)
{
    j.at(0).get_to(v.x);
    j.at(1).get_to(v.y);
}

constexpr const std::string_view ADD_TITLE = "add_title";
constexpr const std::string_view ADD_GRID = "add_grid";
constexpr const std::string_view ADD_POINT = "add_point";
constexpr const std::string_view ADD_LINE_SEGMENT = "add_line_segment";

Visualizer::Visualizer()
{
    title_font.loadFromFile("/usr/share/fonts/TTF/IosevkaNerdFontMono-Heavy.ttf");
    title.setFont(title_font);
    title.setCharacterSize(30);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::White);
    setTitle("Starting title");
}

void Visualizer::load_file()
{
    std::ifstream in("/home/tadeuszk/projects/Algorytmy-Geometryczne/commands.json");
    json data = json::parse(in);

    std::map<std::string, std::function<void(const json &)>> command_to_parser{};
    command_to_parser["add_title"] = [&](const json &js) { setTitle(js.at("title")); };
    command_to_parser["add_grid"] = [&](const json &js) {
        draw_sequence.push_back([](sf::RenderWindow &win) { drawGrid(win, 10, 10); });
    };
    command_to_parser["add_point"] = [&](const json &js) {
        float x = js.at("x");
        float y = js.at("y");

        draw_sequence.push_back([=](sf::RenderWindow &win) {
            sf::CircleShape point{10.0f};
            point.setPosition(x, y);
            win.draw(point);
        });
    };
    command_to_parser["add_line_segment"] = [&](const json &js) {
        json points = js.at("points");
        json p1 = points.at(0);
        json p2 = points.at(1);

        sf::Vector2f point1;
        point1.x = p1.at(0);
        point1.y = p1.at(1);

        sf::Vector2f point2;
        point2.x = p2.at(0);
        point2.y = p2.at(1);

        draw_sequence.push_back([=](sf::RenderWindow &win) {
            sf::Vertex line[] = {sf::Vertex(point1), sf::Vertex(point2)};

            win.draw(line, 2, sf::Lines);
        });
    };

    command_to_parser["add_line"] = [&](const json &js) {
        json points = js.at("points");
        json p1 = points.at(0);
        json p2 = points.at(1);

        sf::Vector2f point1;
        point1.x = p1.at(0);
        point1.y = p1.at(1);
        point1.x *= 100;
        point1.y *= 100;

        sf::Vector2f point2;
        point2.x = p2.at(0);
        point2.y = p2.at(1);
        point2.x *= 100;
        point2.y *= 100;

        draw_sequence.push_back([=](sf::RenderWindow &win) {
            sf::Vertex line[] = {sf::Vertex(point1), sf::Vertex(point2)};
            win.draw(line, 2, sf::Lines);
        });
    };

    for (auto &segment : data) {
        if (!segment.contains("command"))
            std::cerr << "Segment does not contain 'command' field: " << segment << '\n';
        std::string command = segment.at("command");
        if (!command_to_parser.contains(command)) {
            std::cerr << "Unknown command: " << command << '\n';
        } else {
            command_to_parser.at(command)(segment);
        }
    }
}

sf::Text Visualizer::getTitle() const
{
    return title;
}

void Visualizer::setTitle(const std::string &text)
{
    title.setString(text);

    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
}

void Visualizer::onResize(const sf::RenderWindow &window)
{
    auto center = window.getView().getCenter();
    title.setPosition(sf::Vector2f{center.x, 0.0});
    std::cout << title.getPosition().x << '\n';
}
