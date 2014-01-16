// ------------------------------------------------------------------------------------------------
// File:			Pair.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef PAIR_H
#define PAIR_H
#include <math.h>
namespace wick
{
	class Pair
	{
	public:

		double x_;
		double y_;

		// Constructors.
		Pair(double x, double y);
		Pair(int x, int y);
		Pair(const Pair& other);
		Pair();

		// Methods determining distance and angle.
		double distance(const Pair& other);
		double angle(const Pair& other);

		// Operator overloads.
		Pair operator+(const Pair& other) const;
		Pair operator-(const Pair& other) const;
		Pair operator*(const Pair& other) const;
		Pair operator/(const Pair& other) const;
		bool operator==(const Pair& other);
		bool operator!=(const Pair& other) const;
		Pair operator+(const double i) const;
		Pair operator-(const double i) const;
		Pair operator*(const double i) const;
		Pair operator/(const double i) const;
	};
}
#endif
