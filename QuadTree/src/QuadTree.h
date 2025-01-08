#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <vector>
class QuadTreeNode {
private:
    sf::Vector2f m_pos;
    float m_size;
    std::vector<QuadTreeNode> m_nodes;

public:
    QuadTreeNode() {}
    QuadTreeNode(sf::Vector2f pos, float size);
    void subdivide(int depth);
    std::vector<QuadTreeNode> getNodes() { return m_nodes; }
    sf::Vector2f getPos() { return m_pos; }
    float getSize() { return m_size; }
    

};

class QuadTree {

private:
    QuadTreeNode m_node;

    int m_depth;

public:
    enum index {
        topLeft = 0,    //00
        topRight = 2,   //10
        bottomLeft = 1, //01
        bottomRight = 3 //11
    };

    QuadTree(sf::Vector2f pos, float size, int depth);

};

