#include "ImageToVoxelGenerator.h"


ImageToVoxelGenerator::ImageToVoxelGenerator() :
m_tree(sf::Vector2f(0, 0), 2000, 7){

}

void ImageToVoxelGenerator::generate() {
    int cells = pow(2, m_tree.getDepth());

    for (int x = 0; x < cells; x++) {
        for (int y = 0; y < cells; y++) {
            sf::Vector2f pos = m_tree.getPos();

            pos.x += x;
            pos.y += y;

        }
    }


}