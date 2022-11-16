#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--; 
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}


void Model::rotate(sf::Vector3f angles) {

    for (auto& vert : verts_)
    {
        float tmp = vert.y;
        vert.y = vert.y * cos(angles.x) + vert.z * sin(angles.x);
        vert.z = tmp * -sin(angles.x) + vert.z * cos(angles.x);

        tmp = vert.x;
        vert.x = vert.x * cos(angles.y) + vert.z * sin(angles.y);
        vert.z = tmp * -sin(angles.y) + vert.z * cos(angles.y);

        tmp = vert.x;
        vert.x = vert.x * cos(angles.z) + vert.y * sin(angles.z);
        vert.y = tmp * -sin(angles.z) + vert.y * cos(angles.z);

        if (vert.x < -1 || vert.y < -1 || vert.z < -1)
        {
            int i = 0;
            i++;
        }
    }
}


void Model::traslate(sf::Vector3f traslation) {

    for (auto &vert : verts_)
    {
        vert.x += traslation.x;
        vert.y += traslation.y;
        vert.z += traslation.z;
    }

}

void Model::scale(sf::Vector3f scales) {

    for (auto &vert : verts_)
    {
        vert.x *= scales.x;
        vert.y *= scales.y;
        vert.z *= scales.z;
    }
}
