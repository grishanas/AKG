#pragma once


#include "geometry.h"
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

class Camera 
{
	private:
		sf::Vector3f _Position;
		sf::Vector3f _Rotation;
		sf::Vector3f _Target;

		sf::Vector3f _Direcction;
		sf::Vector3f _CameraRight;
		sf::Vector3f _CameraUp;

		void _ChangeCameraView();
		sf::Vector3f Normilize(sf::Vector3f NonNormVector);
	public:

		Camera();
		~Camera();
		void ChangePosition(sf::Vector3f ChangePosition);





};