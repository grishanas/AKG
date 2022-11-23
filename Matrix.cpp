#include "Matrix.h"

sf::Vector3f Normilize(sf::Vector3f NonNormVector)
{
	float length = sqrt(NonNormVector.x * NonNormVector.x + NonNormVector.y * NonNormVector.y + NonNormVector.z * NonNormVector.z);
	if (length == 0)
		return NonNormVector;
	sf::Vector3f newVect = sf::Vector3f(NonNormVector.x / length, NonNormVector.y / length, NonNormVector.z / length);
	return newVect;
}

sf::Vector3f Cross(sf::Vector3f a, sf::Vector3f b)
{
	sf::Vector3f newVect = sf::Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	return newVect;
}

float DotProduct(sf::Vector3f a, sf::Vector3f b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float FindAngle(sf::Vector3f a, sf::Vector3f b)
{
	float temp1 = pow(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2), 0.5);
	float temp2 = pow(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2), 0.5);
	float ab = DotProduct(a, b);
	return ab / (temp1 * temp2);
}