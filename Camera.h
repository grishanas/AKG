#pragma once


#include "geometry.h"
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include "model.h"


struct CameraParametr 
{
	int width;
	int height;
	double z_near, z_far;
};

class Camera 
{
	private:
		CameraParametr Parametr;
		sf::Vector3f _decartCoords;
		/*sf::Vector3f _Rotation;
		sf::Vector3f _Target;*/
		float _collider;

		sf::Vector3f _target;
		sf::Vector2f _angles;
		float _radius;

		sf::Vector3f _direction;
		sf::Vector3f _cameraRight;
		sf::Vector3f _cameraUp;


		void _ChangeCameraView();
		void _SphereToDecart();
		sf::Vector3f _CameraView(sf::Vector3f point);
		
	public:
		void SetFar(double value) { };//Parametr.z_far = value+200.f; };
		void SetNear(double value) { };//Parametr.z_near = value+0.5f; };
		//void SetCollaider(float value) { if (_collider == 0) { _radius = this->_decartCoords.z - value; _collider = _radius + _radius / 2; this->SetDecart(); } else _collider = value; };
		Camera();
		~Camera();
		void Render(Model *model);
		sf::Vector3f Render(sf::Vector3f);
		void SetDecart();
		void ChangeAngle(sf::Vector2f angles);
		void ChangeRadius(float rad);
		sf::Vector3f MatrixProjection(sf::Vector3f point);
		sf::Vector3f MatrixPerspective(sf::Vector3f point);
		sf::Vector3f MatrixviewPort(sf::Vector3f point);


		sf::Vector3f getDecartPos() { return _decartCoords; }




};