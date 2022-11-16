#include "Camera.h"
#include <SFML/System.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


void  Camera::ChangeAngle(sf::Vector2f angles) {

	this->_angles += angles;

	_angles.x = fmod(_angles.x, 2 * M_PI);
    if (_angles.x < 0)
		_angles.x += 2 * M_PI;

	_angles.y = fmod(_angles.y, 2 * M_PI);
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
	this->_SphereToDecart();
	this->_ChangeCameraView();
}

Camera::Camera() 
{
	this->_radius = 2;
	this->Parametr.height=800;
	this->Parametr.width=800;
	this->Parametr.z_near = 0;
	this->Parametr.z_far = 1;
	_target = sf::Vector3f(0, 0, 0);
	this->SetDecart();

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
	sf::Vector3f newVect = sf::Vector3f(a.y*b.z-a.z*b.y,a.x*b.z-a.z*b.x,a.x*b.y-a.y*b.x );
	return newVect;
}

void Camera::_ChangeCameraView() 
{
	this->_direction = Normilize(this->_decartCoords - this->_target);
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
	}
}

sf::Vector3f Camera::_CameraView(sf::Vector3f point)
{
	sf::Vector3f newPoint;

	sf::Vector3f tmp = -Cross(this->_cameraRight, this->_decartCoords);
	tmp = -Cross(this->_cameraUp, this->_decartCoords);
	tmp = -Cross(this->_direction, this->_decartCoords);
	newPoint.x = point.x * this->_cameraRight.x + point.x * this->_cameraRight.y + point.x * this->_cameraRight.z;
	newPoint.y = point.y * this->_cameraUp.x + point.y * this->_cameraUp.y + point.y * this->_cameraUp.z;
	newPoint.z = point.z * this->_direction.x + point.z * this->_direction.y + point.z * this->_direction.z;
	return newPoint;
}

sf::Vector3f Camera::MatrixProjection(sf::Vector3f point)
{
	sf::Vector3f newPoint;
	newPoint.x = point.x * 2 / this->Parametr.width;
	newPoint.y = point.y * 2 / this->Parametr.height;
	newPoint.z = point.z / (this->Parametr.z_near-this->Parametr.z_far) - point.z *this->Parametr.z_near/(this->Parametr.z_near+this->Parametr.z_far);
	return newPoint;
}

sf::Vector3f  Camera::MatrixPerspective(sf::Vector3f point)
{
	sf::Vector3f newPoint;
	float w = this->Parametr.z_near * this->Parametr.z_far / (this->Parametr.z_near - this->Parametr.z_far);

	newPoint.x = point.x * 2*this->Parametr.z_near / this->Parametr.width/w;
	newPoint.y = point.y * 2 * this->Parametr.z_near / this->Parametr.height/w;
	newPoint.z = (point.z * 2* this->Parametr.z_far / (this->Parametr.z_near - this->Parametr.z_far) - point.z)/w;
	return newPoint;
}

sf::Vector3f Camera::MatrixviewPort(sf::Vector3f point)
{
	sf::Vector3f newPoint;

	newPoint.x = point.x * this->Parametr.width/2;
	newPoint.y = point.y * this->Parametr.height/2;
	newPoint.z = point.z;
	return newPoint;
}

sf::Vector3i Camera::Render(sf::Vector3f point)
{
	sf::Vector3f temp;

	temp = this->_CameraView(point);
	temp = this->MatrixProjection(temp);
	temp = this->MatrixviewPort(temp);


	sf::Vector3i newPoint = sf::Vector3i((temp.x+1.)* this->Parametr.width / 2, (temp.y + 1.) * this->Parametr.height / 2, temp.z);
	return newPoint;
}

//void Camera::Render(Model* model)
//{
//	for (int i = 0; i < model->nverts(); i++)
//	{
//		auto vec = model->vert(i);
//		sf::Vector3f tmp;
//
//		//for (int k = 0; k < 3; k++)
//		//{
//		//	tmp.x = vec.x * this->_Rotation.x+ vec.x * this->_Rotation.y+ vec.x * this->_Rotation.z;
//		//	tmp.y = vec.y * this->_Rotation.x+ vec.y * this->_Rotation.y+ vec.y * this->_Rotation.z;
//		//	tmp.z = vec.z * this->_Rotation.x+ vec.z * this->_Rotation.y+ vec.z * this->_Rotation.z;
//		//}
//	}
//}
//sf::Vector3f Camera::Rende(sf::Vector3f a)
//{
//
//
//}

void Camera::_SphereToDecart()
{
	this->_decartCoords.x = this->_radius * sin(1-_angles.y) * cos(_angles.x);
	this->_decartCoords.y = this->_radius * sin(1-_angles.y) * sin(_angles.x);
	this->_decartCoords.z = this->_radius * cos(1-_angles.y);
}
