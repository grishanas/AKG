#include "Camera.h"
#include <SFML/System.hpp>
#include <math.h>


void  Camera::ChangeAngle(sf::Vector2f angles) {

	this->_angles += angles;

	_angles.x = fmod(x, 2 * M_PI);
    if (_angles.x < 0)
        _angles.x += 2 * M_PI;

	_angles.y = fmod(y, 2 * M_PI);
    if (_angles.y < 0)
        _angles.y += 2 * M_PI;

	this->SetDecart();
}

void  Camera::ChangeRadius(float rad) {

	this->_radius += rad;
	this->SetDecart();

}


void Camera::SetDecart() 
{
	this->_decartCoords = _SphereToDecart();
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
	this->_direction = Normilize(this->_decartCoords - sf::Vector3f(.0f,.0f,.0f));
	this->_cameraRight = Normilize(Cross(sf::Vector3f(.0f, 1.f, .0f), this->_direction));
	this->_cameraUp = Normilize(Cross(this->_direction, this->_cameraRight));
}

void Camera::Render(Model* model)
{
	for (int i = 0; i < model->nverts(); i++)
	{
		auto vec = model->vert(i);
		sf::Vector3f tmp;

		for (int k = 0; k < 3; k++)
		{
			//tmp.x = vec.x * this->_rotation.x+ vec.x * this->_Rotation.y+ vec.x * this->_Rotation.z;
			//tmp.y = vec.y * this->_rotation.x+ vec.y * this->_Rotation.y+ vec.y * this->_Rotation.z;
			//tmp.z = vec.z * this->_rotation.x+ vec.z * this->_rotation.y+ vec.z * this->_Rotation.z;
		}
		this->_direction = Normilize(this->_decartCoords - this->_Target);
		sf::Vector3f tmp = Cross(sf::Vector3f(.0f, 1.f, .0f), this->_direction);
		this->_cameraRight = Normilize(tmp);
		this->_cameraUp = Normilize(Cross(this->_direction, this->_CameraRight));
	}

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
//sf::Vector3f Camera::Rende(sf::Vector3f a)
//{
//
//
//}

void Camera::_SphereToDecart()
{
	this->_decartCoords.x = this->_radius * sin(_angles.y) * cos(_angles.x);
	this->_decartCoords.y = this->_radius * sin(_angles.y) * sin(_angles.x);
	this->_decartCoords.z = this->_radius * cos(_angles.y);
}
