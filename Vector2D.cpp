/*
 * Vector2D.cpp
 *
 *  Created on: 28.9.2016
 *      Author: mmriera
 */

#include "Vector2D.h"

template <class T>
Vector2D<T>::Vector2D()
{

	x=0;
	y=0;
	length=0;

}

template <class T>
Vector2D<T>::Vector2D(T a, T b)
{

	x=a;
	y=b;
	length=sqrt(pow(a,2)+pow(b,2));

}

template <class T>
Vector2D<T> Vector2D<T>::operator+ (const Vector2D<T>& argu)
{
	Vector2D<T> result(x + argu.x, y + argu.y);
	return result;
}

template <class T>
Vector2D<T> Vector2D<T>::operator- (const Vector2D<T>& argu)
{
	Vector2D<T> result(x - argu.x, y - argu.y);
	return result;
}

template <class T>
T Vector2D<T>::operator* (const Vector2D<T>& argu)
{

	return x*argu.x + y*argu.y;

}

template <class T>
void Vector2D<T>::MakeUnit()
{
	if(length!=0)
	{
		x=x/length;
		y=y/length;
	}
	else
	{
		std::cout << "Vector2D::MakeUnit() --> Vector length equal to 0, you don't want to divide by 0...\n";
	}
	return;
}

template <class T>
Vector2D<T>::~Vector2D() {
	// TODO Auto-generated destructor stub
}

//instantiation of the types that the template will use
template class Vector2D<float>;
