#ifndef __MATH_VECTOR3
#define __MATH_VECTOR3

#include"MemoryPool.h"
#include<math.h>

namespace Engine
{
	
class Vector3
{


private:

	float	x,y,z;

public:
	//void * Engine::Vector3::operator new();

	void * operator new(unsigned int size);
	void operator delete(void *ptr);

	Vector3( void ) { }		//zero argument constructor.

							
	inline Vector3( const float i_x, const float i_y, const float i_z ); //3 arguments constructor 
	
	inline Vector3( const Vector3 & i_rhs );   //copy constructor

	 //getter methods
	inline const float getx( void ) const;
	inline const float gety( void ) const;
	inline const float getz( void ) const;
	
	//setter methods
	inline void setx( const float i_x );
	inline void sety( const float i_y );
	inline void setz( const float i_z );

	inline void display();

	//in class operators
	inline const Vector3 & operator =( const Vector3 & i_rhs );
	inline const Vector3 & operator +=( const Vector3 & i_rhs );
	inline const Vector3 & operator -=( const Vector3 & i_rhs );
    inline const Vector3 & operator *=( const Vector3 & i_rhs );  //cross product of vector
    inline const Vector3 & operator |=( const Vector3 & i_rhs );  //dot product of vector
	inline bool operator ==( const Vector3 & i_rhs );
	inline bool operator !=( const Vector3 & i_rhs );

	float Length();
	Engine::Vector3 Normalize();

	
} ;

}

//outside class operators
inline const Engine::Vector3 operator+( const Engine::Vector3 & i_lhs, const Engine::Vector3 & i_rhs );
inline const Engine::Vector3 operator-( const Engine::Vector3 & i_lhs, const Engine::Vector3 & i_rhs );
inline const Engine::Vector3 operator*( const Engine::Vector3 & i_lhs, const Engine::Vector3 & i_rhs );//cross product of vector
inline const Engine::Vector3 operator*( const Engine::Vector3 & i_lhs, const float i_value);
inline const Engine::Vector3 operator|( const Engine::Vector3 & i_lhs, const Engine::Vector3 & i_rhs );   //dot product of vector


#include "vector3.inl"


#endif 