
#include "Util.h"


Engine::Vector2::Vector2( const float i_x, const float i_y ) :
	x( i_x ),
	y( i_y )
{
	
	assert( !IsNAN( i_x ) );
	assert( !IsNAN( i_y ) );
}

Engine::Vector2::Vector2( const Vector2 & i_rhs ) :
	x( i_rhs.x ),
	y( i_rhs.y )
	
{
	
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );

}


// getter methods
const float Engine:: Vector2::getx( void ) const
{
	return x;
}

const float Engine:: Vector2::gety( void ) const
{
	return y;
}



//setter methods
void Engine:: Vector2::setx( float i_x )
{
	assert( !IsNAN( i_x ) );
	
	x = i_x;
}

void Engine:: Vector2::sety( float i_y )
{
	assert( !IsNAN( i_y ) );
	
	y = i_y;
}




void Engine::Vector2::display() 
{
	printf("[%f  %f  %f]\n\n",x,y);
}

//in class operators
inline const  Engine::Vector2 & Engine::Vector2::operator=( const Engine::Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );


	x = i_rhs.x;
	y = i_rhs.y;


	return *this;
}


inline const Engine::Vector2 & Engine:: Vector2::operator+=( const Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );


	x=x+i_rhs.x;
	y=y+i_rhs.y;

	return *this;

}



inline const Engine::Vector2 & Engine::Vector2::operator-=( const Engine::Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	

	x=x-i_rhs.x;
	y=y-i_rhs.y;

	return *this;

}





inline const Engine::Vector2 & Engine:: Vector2::operator|=( const Engine::Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );
	

	x=x*i_rhs.x;
	y=y*i_rhs.y;


	return *this;

}

inline bool Engine:: Vector2::operator==( const Engine:: Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );


	if( Engine::areRelativelyEqual(x,i_rhs.x) && Engine::areRelativelyEqual(y,i_rhs.y) )
		return (true);
	else
		return (false);

}


inline bool Engine::Vector2::operator!=( const Engine::Vector2 & i_rhs )
{
	assert( !IsNAN( i_rhs.x ) );
	assert( !IsNAN( i_rhs.y ) );

	if( x!=i_rhs.x ||	y!=i_rhs.y)
		return (true);
	else
		return (false);

}


//outside class operators
inline const Engine:: Vector2 operator+( const Engine::Vector2 & i_lhs, const Engine:: Vector2 & i_rhs )
{
	
	Engine::Vector2 t;
	t.setx(i_lhs.getx()+i_rhs.getx());
	t.sety(i_lhs.gety()+i_rhs.gety());

    return t;
}


inline const Engine:: Vector2 operator-( const Engine:: Vector2 & i_lhs, const Engine::Vector2 & i_rhs )
{
	
	Engine::Vector2 t;
	t.setx(i_lhs.getx()-i_rhs.getx());
	t.sety(i_lhs.gety()-i_rhs.gety());
    return t;
}




inline const Engine::Vector2 operator*( const Engine::Vector2 & i_lhs, const float i_value )
{

	Engine::Vector2 t;
	t.setx( i_lhs.getx()* i_value );
	t.sety( i_lhs.gety()* i_value );
    return t;
}

inline const Engine::Vector2 operator *( const Engine:: Vector2 & i_lhs, const Engine:: Vector2 & i_rhs )
{
	
	Engine::Vector2 t;
	t.setx(i_lhs.getx()*i_rhs.getx());
	t.sety(i_lhs.gety()*i_rhs.gety());
    return t;
}

