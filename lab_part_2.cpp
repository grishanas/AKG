#include "Lab_part_2.h"

void Restarization() 
{

}

void ZBuffering(Model* model, pix* pixarray)
{
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++)
		{
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);

		}


	}

	return;
}