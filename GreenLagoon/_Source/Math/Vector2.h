#ifndef __MATH_VECTOR2
#define __MATH_VECTOR2

#include<assert.h>
#include<math.h>
#include<stdio.h>

namespace Engine
{
	
class Vector2
{


private:

	float	x,y;

public:

	Vector2( void ) { }		//zero argument constructor.

							
	inline Vector2( const float i_x, const float i_y ); //3 arguments constructor 
	
	inline Vector2( const Vector2 & i_rhs );   //copy constructor

	 //getter methods
	inline const float getx( void ) const;
	inline const float gety( void ) const;
	
	//setter methods
	inline void setx( const float i_x );
	inline void sety( const float i_y );


	inline void display();

	//in class operators
	inline const Vector2 & operator =( const Vector2 & i_rhs );
	inline const Vector2 & operator +=( const Vector2 & i_rhs );
	inline const Vector2 & operator -=( const Vector2 & i_rhs );
   // inline const Vector2 & operator *=( const Vector2 & i_rhs );  //cross product of vector
    inline const Vector2 & operator |=( const Vector2 & i_rhs );  //dot product of vector
	inline bool operator ==( const Vector2 & i_rhs );
	inline bool operator !=( const Vector2 & i_rhs );

	float Length();
	Engine::Vector2 Normalize();

	
} ;

}

//outside class operators
inline const Engine::Vector2 operator+( const Engine::Vector2 & i_lhs, const Engine::Vector2 & i_rhs );
inline const Engine::Vector2 operator-( const Engine::Vector2 & i_lhs, const Engine::Vector2 & i_rhs );
//inline const Engine::Vector2 operator*( const Engine::Vector2 & i_lhs, const Engine::Vector2 & i_rhs );//cross product of vector
inline const Engine::Vector2 operator*( const Engine::Vector2 & i_lhs, const float i_value);
inline const Engine::Vector2 operator*( const Engine::Vector2 & i_lhs, const Engine::Vector2 & i_rhs );   //dot product of vector


#include "Vector2.inl"


#endif 