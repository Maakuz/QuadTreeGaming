#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "src/QuadTree.h"

class ImageToVoxelGenerator {
private:
    sf::Texture m_texture;
    QuadTree<int> m_tree;

    void generate();
public:
    ImageToVoxelGenerator();
};

