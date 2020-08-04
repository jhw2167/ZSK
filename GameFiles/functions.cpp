
//includes
#include "functions.h"

/*
	Implementation file for functions.h with functions definitions in the 
	namespace zsk tailored to this game
*/

namespace zsk 
{
	zsk::vect randomSpawn(const vect& range_x, const vect& range_y)
	{
		//vect.a = min, vect.b = max range

		try
		{
			static int srand(time(0));

			float rand_x = (rand() % ((int)range_x.b - (int)range_x.a));
			rand_x += (int)range_x.a;
			//Calculated our rand x w/in provided range

			float rand_y = (rand() % ((int)range_y.b - (int)range_y.a));
			rand_y += (int)range_y.a;
			//Calculated our rand x w/in provided range

			return vect(rand_x, rand_y);
		}
		catch (const std::exception& e)
		{
			cout << "Exception caight in global funtion zsk::randomSpawn" <<
				" possible attempt to modulo 0 " << endl;
			cout << e.what() << endl;
		}

		return range_x;
	}

	float distanceFrom(const sf::Vector2f & loc1, const sf::Vector2f & loc2)
	{
		//calculates vector distance from player or tower object

		float xDist = abs(loc1.x - loc2.x);
		float yDist = abs(loc1.y - loc2.y);
		//calculates x and y distances away follower is from player

		return pow(xDist * xDist + yDist * yDist, 0.5);
		//calculates vector for distance from follower to player
	}

	float magnitude(float x, float y)
	{
		float xVal = x * x;
		float yVal = y * y;

		return sqrt(xVal + yVal);
	}

	double radsToDegs(double rads) {
		return rads * (180.f / pi);
	}

}