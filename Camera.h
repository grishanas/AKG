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
		sf::Vector3f _decartCoords;
		/*sf::Vector3f _Rotation;
		sf::Vector3f _Target;*/

		sf::Vector2f _angles;
		float _radius;

		sf::Vector3f _direction;
		sf::Vector3f _cameraRight;
		sf::Vector3f _cameraUp;


		void _ChangeCameraView();

		void _SphereToDecart();
		
	public:
		void SetFar(double value) { Parametr.z_far = value; };
		void SetNear(double value) { Parametr.z_near = value; };
		double GetFar() {return  Parametr.z_far; };
		double GetNear(){return Parametr.z_near; };
		Camera();
		~Camera();
		void Render(Model *model);
		sf::Vector3f Render(sf::Vector3f);
		void SetDecart();
		void ChangeAngle(sf::Vector2f angles);
		void ChangeRadius(float rad);


		sf::Vector3f getDecartPos() { return _decartCoords; }




};