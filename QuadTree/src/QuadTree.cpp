#include "QuadTree.h"

QuadTreeNode::QuadTreeNode(sf::Vector2f pos, float size) {
    m_pos = pos;
    m_size = size;
}

void QuadTreeNode::subdivide(int depth) {
    m_nodes.resize(4);

    for (int i = 0; i < m_nodes.size(); i++) {
        sf::Vector2f newPos = m_pos;

        if ((i & 2) == 2) {
            newPos.x += m_size * 0.25f;
        }

        else {
            newPos.x -= m_size * 0.25f;
        }

        if ((i & 1) == 1) {
            newPos.y += m_size * 0.25f;
        }

        else {
            newPos.y -= m_size * 0.25f;
        }

        m_nodes[i] = QuadTreeNode(newPos, m_size * 0.5f);
        if (depth > 0)
            m_nodes[i].subdivide(depth - 1);
    }

    int d = 0;
}

QuadTree::QuadTree(sf::Vector2f pos, float size, int depth):
m_node(pos, size) {
    m_depth = 0;
    m_node.subdivide(depth);
}
