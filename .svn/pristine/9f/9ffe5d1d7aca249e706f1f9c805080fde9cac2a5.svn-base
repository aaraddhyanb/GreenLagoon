
#include "Util.h"


Engine::Vector3::Vector3( const float i_x, const float i_y, const float i_z ) :
	x( i_x ),
	y( i_y ),
	z( i_z )
{
	
	assert( !IsNAN( i_x ) );
	assert( !IsNAN( i_y ) );
	assert( !IsNAN( i_z ) );
}

Engine::Vector3::Vector3( const Vector3 & i_rhs ) :
	x( i_rhs.x ),
	y( i_rhs.y ),
	z( i_rhs.z )
{
	
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );
}


// getter methods
const float Engine:: Vector3::getx( void ) const
{
	return x;
}

const float Engine:: Vector3::gety( void ) const
{
	return y;
}

const float Engine:: Vector3::getz( void ) const
{
	return z;
}


//setter methods
void Engine:: Vector3::setx( float i_x )
{
	assert( !IsNAN( i_x ) );
	
	x = i_x;
}

void Engine:: Vector3::sety( float i_y )
{
	assert( !IsNAN( i_y ) );
	
	y = i_y;
}

void Engine:: Vector3::setz( float i_z )
{
	assert( !IsNAN( i_z ) );
	
	z = i_z;
}


void Engine::Vector3::display() 
{
	printf("[%f  %f  %f]\n\n",x,y,z);
}

//in class operators
inline const  Engine::Vector3 & Engine::Vector3::operator=( const Engine::Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	x = i_rhs.x;
	y = i_rhs.y;
	z = i_rhs.z;

	return *this;
}


inline const Engine::Vector3 & Engine:: Vector3::operator+=( const Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	x=x+i_rhs.x;
	y=y+i_rhs.y;
	z=z+i_rhs.z;

	return *this;

}



inline const Engine::Vector3 & Engine::Vector3::operator-=( const Engine::Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	x=x-i_rhs.x;
	y=y-i_rhs.y;
	z=z-i_rhs.z;

	return *this;

}


inline const Engine::Vector3 & Engine::Vector3::operator*=( const Engine::Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	x=(y*i_rhs.z)-(i_rhs.y*z);
	y=(x*i_rhs.z)-(i_rhs.x*z);
	z=(x*i_rhs.y)-(i_rhs.x*y);

	return *this;

}


inline const Engine::Vector3 & Engine:: Vector3::operator|=( const Engine::Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	x=x*i_rhs.x;
	y=y*i_rhs.y;
	z=z*i_rhs.z;

	return *this;

}

inline bool Engine:: Vector3::operator==( const Engine:: Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	if( Engine::areRelativelyEqual(x,i_rhs.x) && Engine::areRelativelyEqual(y,i_rhs.y) && Engine::areRelativelyEqual(z,i_rhs.z))
		return (true);
	else
		return (false);

}


inline bool Engine::Vector3::operator!=( const Engine::Vector3 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	assert( !IsNAN( i_rhs.z ) );

	if( x!=i_rhs.x ||	y!=i_rhs.y || z!=i_rhs.z)
		return (true);
	else
		return (false);

}


//outside class operators
inline const Engine:: Vector3 operator+( const Engine::Vector3 & i_lhs, const Engine:: Vector3 & i_rhs )
{
	
	Engine::Vector3 t;
	t.setx(i_lhs.getx()+i_rhs.getx());
	t.sety(i_lhs.gety()+i_rhs.gety());
	t.setz(i_lhs.getz()+i_rhs.getz());
    return t;
}


inline const Engine:: Vector3 operator-( const Engine:: Vector3 & i_lhs, const Engine::Vector3 & i_rhs )
{
	
	Engine::Vector3 t;
	t.setx(i_lhs.getx()-i_rhs.getx());
	t.sety(i_lhs.gety()-i_rhs.gety());
	t.setz(i_lhs.getz()-i_rhs.getz());
    return t;
}


inline const Engine::Vector3 operator*( const Engine::Vector3 & i_lhs, const Engine::Vector3 & i_rhs )
{

	Engine::Vector3 t;
	t.setx( (i_lhs.gety()*i_rhs.getz() )-( i_rhs.gety()*i_lhs.getz()) );
	t.sety( (i_lhs.getx()*i_rhs.getz() )-( i_rhs.getx()*i_lhs.getz()) );
	t.setz( (i_lhs.getx()*i_rhs.gety() )-( i_rhs.getx()*i_lhs.gety()) );
    return t;
}


inline const Engine::Vector3 operator*( const Engine::Vector3 & i_lhs, const float i_value )
{

	Engine::Vector3 t;
	t.setx( i_lhs.getx()* i_value );
	t.sety( i_lhs.gety()* i_value );
	t.setz( i_lhs.gety()* i_value );
    return t;
}

inline const Engine::Vector3 operator |( const Engine:: Vector3 & i_lhs, const Engine:: Vector3 & i_rhs )
{
	
	Engine::Vector3 t;
	t.setx(i_lhs.getx()*i_rhs.getx());
	t.sety(i_lhs.gety()*i_rhs.gety());
	t.setz(i_lhs.getz()*i_rhs.getz());
    return t;
}

