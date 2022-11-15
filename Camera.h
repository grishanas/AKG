#pragma once


#include "geometry.h"
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include "model.h"

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
		
	public:

		Camera();
		~Camera();
		void Render(Model *model);
		void ChangePosition(sf::Vector3f ChangePosition);





};