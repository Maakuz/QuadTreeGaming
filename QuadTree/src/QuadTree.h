#pragma once
#include <SFML/Graphics/Transform.hpp>
#include <vector>

template <typename T>
class QuadTree {
public:

    enum index {
        topLeft = 0,    //00
        topRight = 2,   //10
        bottomLeft = 1, //01
        bottomRight = 3 //11
    };

    class QuadTreeNode {
    private:
        sf::Vector2f m_pos;
        float m_size;
        std::vector<QuadTreeNode> m_nodes;
        T m_value;

    public:
        QuadTreeNode() {}
        QuadTreeNode(sf::Vector2f pos, float size);
        void subdivide(sf::Vector2f targetPos, T val, int depth = 0);
        std::vector<QuadTreeNode>* getNodesPtr() { return &m_nodes; }
        sf::Vector2f getPos() const { return m_pos; }
        float getSize() const { return m_size; }
        bool isLeaf() const { return m_nodes.size() == 0; }
    };

private:
    QuadTreeNode m_node;
    int m_depth;

    static int getIndexOfPosition(sf::Vector2f lookupPos, sf::Vector2f nodePos);

public:
    QuadTree(sf::Vector2f pos, float size, int depth);

    QuadTreeNode getRoot() const { return m_node; }
    int getDepth() const { return m_depth; }
    sf::Vector2f getPos() const { return m_node.getPos(); }
    void insert(T val, sf::Vector2f pos);

};

template <typename T>
QuadTree<T>::QuadTreeNode::QuadTreeNode(sf::Vector2f pos, float size) {
    m_pos = pos;
    m_size = size;
};

template <typename T>
void QuadTree<T>::QuadTreeNode::subdivide(sf::Vector2f targetPos, T val, int depth) {
    int index = getIndexOfPosition(targetPos, sf::Vector2f(m_pos.x + (m_size * 0.5f), m_pos.y + (m_size * 0.5f)));
    
    //if it exist just move on to the next layer
    if (!isLeaf()) {
        if (depth > 0)
            m_nodes[index].subdivide(targetPos, val, depth - 1);
        return;
    }

    m_nodes.resize(4);

    for (int i = 0; i < m_nodes.size(); i++) {
        sf::Vector2f newPos = m_pos;

        if ((i & 2) == 2) {
            newPos.x += m_size * 0.5f;
        }

        if ((i & 1) == 1) {
            newPos.y += m_size * 0.5f;
        }

        m_nodes[i] = QuadTreeNode(newPos, m_size * 0.5f);
        if (depth > 0 && index == i)
            m_nodes[i].subdivide(targetPos, val, depth - 1);
    }
}




//SUBCLASS ENDS HERE

template <typename T>
QuadTree<T>::QuadTree(sf::Vector2f pos, float size, int depth) :
    m_node(pos, size) {
    m_depth = depth;
    //m_node.subdivide(depth);
};

template <typename T>
int QuadTree<T>::getIndexOfPosition(sf::Vector2f lookupPos, sf::Vector2f nodePos) {
    int index = 0;

    index = index | (lookupPos.x > nodePos.x ? 2 : 0);
    index = index | (lookupPos.y > nodePos.y ? 1 : 0);

    return index;
};

template<typename T>
inline void QuadTree<T>::insert(T val, sf::Vector2f pos) {
    m_node.subdivide(pos, val, m_depth);
};