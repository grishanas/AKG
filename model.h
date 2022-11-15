#ifndef __MODEL_H__
#define __MODEL_H__

#include <SFML/System/Vector3.hpp>

#include <vector>
#include "geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
	sf::Vector3f rotation_;
	sf::Vector3f transform_;
	sf::Vector3f scale_;

public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	void rotate(sf::Vector3f angles);
	void scale(sf::Vector3f scales);
	void traslate(sf::Vector3f traslation);
	Vec3f vert(int i);
	std::vector<int> face(int idx);
};

#endif //__MODEL_H__
