#include "Camera.h"
#include <SFML/System.hpp>
#include <math.h>


void Camera::ChangePosition(sf::Vector3f ChangePosition) 
{
	this->_Position += ChangePosition;
	
}

sf::Vector3f Normilize(sf::Vector3f NonNormVector)
{
	float length = sqrt(NonNormVector.x * NonNormVector.x + NonNormVector.y * NonNormVector.y + NonNormVector.z * NonNormVector.z);
	sf::Vector3f newVect = sf::Vector3f(NonNormVector.x / length, NonNormVector.y / length, NonNormVector.z / length);
	return newVect;
}

inline sf::Vector3f Cross(sf::Vector3f a, sf::Vector3f b)
{
	sf::Vector3f newVect = sf::Vector3f(a.y*b.z-a.z*b.y,a.x*b.z-a.z*b.x,a.x*b.y+a.z*b.y );
	return newVect;
}

void Camera::_ChangeCameraView() 
{
	// !
	this->_Target.x = this->_Position.x * sin(this->_Rotation.x);
	this->_Target.y = this->_Position.y * sin(this->_Rotation.y);
	this->_Target.z = this->_Position.z * sin(this->_Rotation.z);

	this->_Direcction = this->Normilize(this->_Position - this->_Target);
	this->_CameraRight = this->Normilize(Cross(sf::Vector3f(.0f,1.f,.0f),this->_Direcction));
	this->_CameraUp = this->Normilize(Cross(this->_Direcction, this->_CameraRight));

}