/*
 * Vector2D.h
 *
 *  Created on: 28.9.2016
 *      Author: mmriera
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include<iostream>
#include<cmath>


template<class T>
class Vector2D {
public:
	Vector2D();
	Vector2D(T,T);
	virtual ~Vector2D();

	T x;
	T y;
	T length;

	Vector2D<T> operator + (const Vector2D<T>&);
	Vector2D<T> operator - (const Vector2D<T>&);
	T operator * (const Vector2D<T>&); //dot product

	void MakeUnit();


};


#endif /* VECTOR2D_H_ */
