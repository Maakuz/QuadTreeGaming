#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include "QuadTree.h"

void drawNode(QuadTree<int>::QuadTreeNode* node, sf::RenderWindow* wind, int depth = 0);

int main() {
    sf::RenderWindow window(sf::VideoMode({ 2000, 2000 }), "SFML works!");
    window.setFramerateLimit(120);
    sf::CircleShape shape(10.f);
    shape.setOrigin(sf::Vector2f(10, 10));
    shape.setPosition(sf::Vector2f(570, 570));
    shape.setFillColor(sf::Color::Blue);

    QuadTree<int> tree(sf::Vector2f(0, 0), 2000, 7);
    sf::Clock clock;

    while (window.isOpen())
    {
        float currentTime = clock.restart().asMilliseconds();
        printf("%f\n", currentTime);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            // left mouse button is pressed: shoot
            shape.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
            tree.insert(1, shape.getPosition());
        }

        static bool drawTree = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            drawTree = !drawTree;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(shape);
        auto root = tree.getRoot();
        if (drawTree)
            drawNode(&root, &window);
        window.display();
    }

    return 0;
}

void drawNode(QuadTree<int>::QuadTreeNode* node, sf::RenderWindow* wind, int depth) { 
    if (!node->isLeaf()) {
        for (auto n : *node->getNodesPtr()) {
            drawNode(&n, wind, depth + 1);
        }
    }
    sf::RectangleShape rect(sf::Vector2f(1, 1) * node->getSize());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(0, 255, 0));
    rect.setPosition(node->getPos());
    rect.setOutlineThickness(1);
    wind->draw(rect);
}