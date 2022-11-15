#include "Camera.h"
#include <SFML/System.hpp>
#include <math.h>

void Camera::ChangePosition(sf::Vector3f ChangePosition) 
{
	this->_Position += ChangePosition;
	this->_ChangeCameraView();
}

Camera::Camera() {

}

Camera::~Camera() {
}

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
	sf::Vector3f newVect = sf::Vector3f(a.y*b.z-a.z*b.y,a.x*b.z-a.z*b.x,a.x*b.y+a.z*b.y );
	return newVect;
}

void Camera::_ChangeCameraView() 
{
	// !
	this->_Target.x = this->_Position.x * sin(this->_Rotation.x);
	this->_Target.y = this->_Position.y * sin(this->_Rotation.y);
	this->_Target.z = this->_Position.z * sin(this->_Rotation.z);

	this->_Direcction = Normilize(this->_Position - this->_Target);
	sf::Vector3f tmp = Cross(sf::Vector3f(.0f, 1.f, .0f), this->_Direcction);
	this->_CameraRight = Normilize(tmp);
	this->_CameraUp = Normilize(Cross(this->_Direcction, this->_CameraRight));
}

void Camera::Render(Model* model)
{
	for (int i = 0; i < model->nverts(); i++)
	{
		auto vec = model->vert(i);
		sf::Vector3f tmp;

		for (int k = 0; k < 3; k++)
		{
			tmp.x = vec.x * this->_Rotation.x+ vec.x * this->_Rotation.y+ vec.x * this->_Rotation.z;
			tmp.y = vec.y * this->_Rotation.x+ vec.y * this->_Rotation.y+ vec.y * this->_Rotation.z;
			tmp.z = vec.z * this->_Rotation.x+ vec.z * this->_Rotation.y+ vec.z * this->_Rotation.z;
		}
	}
}
 
sf::Vector3f 