
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


	namespace art
	{
		sf::Image & changePixels(sf::Image & img,
			const sf::Color & cFrom, const sf::Color & cTo, const int slack)
		{
			/*
				We take an image, set the background of the image transpartent
				by comparing to a target color to eliminate.  The more slack,
				the wider the range we will set colored to transpartent.
			*/
			const static int maxColor = 255;
			const static int minColor = 0;


			int r1 = std::min(cFrom.r + slack, maxColor);
			int g1 = std::min(cFrom.g + slack, maxColor);
			int b1 = std::min(cFrom.b + slack, maxColor);
			const sf::Color maxC = sf::Color(r1, g1, b1);

			int r2 = std::max(cFrom.r - slack, minColor);
			int g2 = std::max(cFrom.g - slack, minColor);
			int b2 = std::max(cFrom.b - slack, minColor);
			const sf::Color minC = sf::Color(r2, g2, b2);

			const int sizeX = img.getSize().x;
			const int sizeY = img.getSize().y;

			for (unsigned int x = 0; x != sizeX; x++)
			{
				for (unsigned int y = 0; y != sizeY; y++)
				{
					sf::Color pixColor = img.getPixel(x, y);

					bool inRed = (pixColor.r <= maxC.r) && (pixColor.r >= minC.r);
					bool inGrn = (pixColor.g <= maxC.g) && (pixColor.g >= minC.g);
					bool inBlue = (pixColor.b <= maxC.b) && (pixColor.b >= minC.b);

					if (inRed && inGrn && inBlue) {
						img.setPixel(x, y, cTo);
					}
				}
			}

			return img;
		}





		sf::Image & changePixelRange(sf::Image & img,
			const sf::Color & cFrom, const sf::Color & cTo)
		{
			/*
				Alter pixel RANGE, instead of changing all the pixels in the slack
				range to ONE pixel type, we add the difference of c1 and c2 to 
				complete the transformation 
			*/
			const static int maxColor = 255;
			const static int minColor = 0;

			//Find min color codes between two colors
			int rMin = std::min(cFrom.r, cTo.r);
			int gMin = std::min(cFrom.g, cTo.g);
			int bMin = std::min(cFrom.b, cTo.b);

			int rMax = std::max(cFrom.r, cTo.r);
			int gMax = std::max(cFrom.g, cTo.g);
			int bMax = std::max(cFrom.b, cTo.b);
			
			const sf::Color diff = sf::Color(rMax - rMin,
											gMax - gMin,
											bMax - bMin);

			const int sizeX = img.getSize().x;
			const int sizeY = img.getSize().y;

			for (unsigned int x = 0; x != sizeX; x++)
			{
				for (unsigned int y = 0; y != sizeY; y++)
				{
					sf::Color pixel = img.getPixel(x, y);

					int newR = newCodeFromDiff(rMin, rMax, pixel.r, diff.r);
					int newG = newCodeFromDiff(gMin, gMax, pixel.g, diff.g);
					int newB = newCodeFromDiff(bMin, bMax, pixel.b, diff.b);
					
					const sf::Color newColor = sf::Color(newR, newG, newB, pixel.a);
					img.setPixel(x, y, newColor);

					sf::Vector2f pix = sf::Vector2f(x, y);

					cout << "pixel: (" << pix << ")";
				}
			}

			return img;
		}


		int newCodeFromDiff(int minC, int maxC, int pixC, int diffC)
		{
			/*
				Helper method generates the new color code from the 
				min, max and current pixel color codes
				Helper method for changePixelRange();
			*/

			int minDiff = abs(minC - pixC);
			int maxDiff = abs(maxC - pixC);

			if (minDiff < maxDiff)
				return pixC + diffC;
			else
				return pixC - diffC;

		}

	}

}