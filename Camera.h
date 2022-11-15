#pragma once


#include "geometry.h"
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include "model.h"

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

		Camera();
		~Camera();
		void Render(Model *model);
		void SetDecart();
		void ChangeAngle(sf::Vector2f angles);
		void ChangeRadius(float rad);





};