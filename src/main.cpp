#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

#include "visualizer.h"

int main()
{
    Visualizer visualizer{};
    visualizer.load_file();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(640, 480), "Graphics", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    visualizer.onResize(window);

    sf::Vector2u previous_size = window.getSize();
    //    sf::CircleShape shape(100.f);
    //    shape.setFillColor(sf::Color::Green);
    int max_steps = 0;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        if (ImGui::Button("Look at this pretty button")) {
            std::cout << "Pressed\n";
            max_steps++;
        }
        ImGui::End();

        window.clear();

        // Test

        // end Test
        if (previous_size != window.getSize()) {
            visualizer.onResize(window);
            previous_size = window.getSize();
        }
        int steps = 0;
        for (auto &func : visualizer.draw_sequence) {
            if (++steps > max_steps) {
                break;
            }
            func(window);
        }

        window.draw(visualizer.getTitle());
        //        window.draw(shape);
        ImGui::SFML::Render(window);
        sf::Image img = window.capture();
        window.display();
    }

    ImGui::SFML::Shutdown();
}
