#ifndef GEOMETRY_DATA_HPP
#define GEOMETRY_DATA_HPP

#include <vector>

struct GeometryData {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    GeometryData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {}
};

#endif // !GEOMETRY_DATA_HPP
