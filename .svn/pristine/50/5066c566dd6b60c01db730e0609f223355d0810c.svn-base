#include"AABB.h"

namespace Engine{


bool  AABB::collided=false;
Vector3 AABB::sideNormal=Vector3(0.0,0.0,0.0);
bool AABB::normalXSwaped=false;
bool AABB::normalYSwaped=false;

bool AABB::CheckForCollision(Actor &i_actorA,Actor &i_actorB, float deltaTime)
{	
	collided=false;
	
	//
    Vector3 ActorBposition=*i_actorB.getActorPreviousPosition();
    Vector3 ActorBvelocity=*i_actorB.getActorPreviousVelocity() - *i_actorA.getActorPreviousVelocity();
	
	
	ActorBposition = ActorBposition + ActorBvelocity* deltaTime;

	//shrinking boxB to a point
	Vector2 boxBcoord=Vector2(ActorBposition.getx(),ActorBposition.gety());


	//blow up boxA 
	Vector2 boxAmin,boxAmax;
	/*boxAmin.setx(i_actorA.getBox()->GetMin().getx()-i_actorB.getBox()->GetWidth()/2);
	boxAmin.sety(i_actorA.getBox()->GetMin().gety()-i_actorB.getBox()->GetHeight()/2);
	boxAmax.setx(i_actorA.getBox()->GetMax().getx()+i_actorB.getBox()->GetWidth()/2);
	boxAmax.sety(i_actorA.getBox()->GetMax().gety()+i_actorB.getBox()->GetHeight()/2);
*/
	boxAmin.setx(i_actorA.getActorPreviousPosition()->getx()-(i_actorA.getBox()->GetWidth()/2) - (i_actorB.getBox()->GetWidth()/2) );
	boxAmax.setx(i_actorA.getActorPreviousPosition()->getx()+(i_actorA.getBox()->GetWidth()/2)  + (i_actorB.getBox()->GetWidth()/2) );
	boxAmin.sety(i_actorA.getActorPreviousPosition()->gety()-(i_actorA.getBox()->GetHeight()/2)  -( i_actorB.getBox()->GetHeight()/2) );
	boxAmax.sety(i_actorA.getActorPreviousPosition()->gety()+(i_actorA.getBox()->GetHeight()/2)  + (i_actorB.getBox()->GetHeight()/2 ) );


	//previous position of boxB 
	Vector2 boxBcoordPre=Vector2(i_actorB.getActorPreviousPosition()->getx(),i_actorB.getActorPreviousPosition()->gety() );


	//checking distance and time with Xmax
	float TxEntry;
	{
		const Vector2 centre(boxAmax);
	    Vector2 normal(1,0);
		float distance=((centre- boxBcoordPre) * normal).getx();
		TxEntry=distance/(( boxBcoord-boxBcoordPre) * normal).getx();
	
	}

	//checking distance and time with Xmin
	float TxExit;
	{
		Vector2 centre(boxAmin);
	    Vector2 normal(1,0);
		float distance=((centre- boxBcoordPre) * normal).getx();
		TxExit=distance/((boxBcoord-boxBcoordPre) * normal).getx();
		
	}

	//checking distance and time with Ymax
	float TyEntry;
	{
		Vector2 centre(boxAmax);
	    Vector2 normal(0,1);
		float distance=((centre- boxBcoordPre) * normal).gety();
		TyEntry=distance/(( boxBcoord- boxBcoordPre) * normal).gety();
	
	}
	
	//checking distance and time with Ymin
	float TyExit;
	{
		Vector2 centre(boxAmin);
	    Vector2 normal(0,1);
		float distance=((centre- boxBcoordPre) * normal).gety();
		TyExit=distance/((boxBcoord-boxBcoordPre) * normal).gety();
		
	}

	if(TxEntry> TxExit)
	{
		float temp=TxExit;
		TxExit=TxEntry;
		TxEntry=temp;
	}


	if(TyEntry> TyExit)
	{
		float temp=TyExit;
		TyExit=TyEntry;
		TyEntry=temp;
	}

	if( (TxEntry>=0 && TxEntry<=1 && !isinf(TxEntry) )  ||
		(TyEntry>=0 && TyEntry<=1 && !isinf(TyEntry) ) 	
	  )
	{

	    if( (!isinf(TxEntry) && !isinf(TxExit) )  && (!isinf(TyEntry) && !isinf(TyExit) ) )
		{ 
			if( (TxEntry<=TyExit) && ( TyEntry<=TxExit) &&  TxEntry<=1 && TyEntry<=1) 
      			  collided=true;
		   else 
			  collided=false;
		}
     

	}
	    //if both the boxes are stationary//special case
	 if( (isinf(TxEntry) || isinf(TxExit) )  && (isinf(TyEntry) || isinf(TyExit) ) )
		{
			if( ( boxBcoord.getx() >= boxAmin.getx() && boxBcoord.getx() <=boxAmax.getx() ) &&
				( boxBcoord.gety() >= boxAmin.gety() && boxBcoord.gety() <=boxAmax.gety() ) )
			      collided=true;
		        else 
			      collided=false;
		}

	   //If delta X is zero //special case
	 if( (isinf(TxEntry) || isinf(TxExit) )  && ( !isinf(TyEntry) && !isinf(TyExit) ) )
		{
			if( ( boxBcoord.getx() >= boxAmin.getx() && boxBcoord.getx() <=boxAmax.getx() ) && (TyEntry>=0 && TyEntry<=1 ) )
				   collided=true;
		        else 
			      collided=false;
		} 

	    //If delta Y is zero //special case
		if( (isinf(TyEntry) || isinf(TyExit) ) && ( !isinf(TxEntry) && !isinf(TxExit) ) ) 
		{
			if( (boxBcoord.gety() >= boxAmin.gety() && boxBcoord.gety() <=boxAmax.gety() ) && (TxEntry>=0 && TxEntry<=1 ) )
			       collided=true;
		        else 
			      collided=false;
		}

		
			if( (TyEntry<=0) && (TxEntry<=0) && (TxExit>=1) &&(TyExit>=1) )
				collided=true;
		

	return 0;
}

bool AABB::isCollided()
{
	return collided;
}

Vector3 AABB::checkNormal()
{
	return sideNormal;
}

bool AABB::CheckForCollision(Actor &i_actorA,Vector3 i_positionA,Vector3 i_positionB, Vector3 i_velocityA,Vector3 i_velocityB, float i_width,float i_height,float deltaTime)
{	
	collided=false;
	normalXSwaped=false;
    normalYSwaped=false;

	//
    Vector3 ActorBposition=i_positionB;
    Vector3 ActorBvelocity= i_velocityB-i_velocityA;
	
	
	ActorBposition = ActorBposition + ActorBvelocity* deltaTime;

	//shrinking boxB to a point
	Vector2 boxBcoord=Vector2(ActorBposition.getx(),ActorBposition.gety());


	//blow up boxA 
	Vector2 boxAmin,boxAmax;

	boxAmin.setx(i_positionA.getx()-(i_actorA.getBox()->GetWidth()/2) - i_width/2 );
	boxAmax.setx(i_positionA.getx()+(i_actorA.getBox()->GetWidth()/2)  + i_width/2 );
	boxAmin.sety(i_positionA.gety()-(i_actorA.getBox()->GetHeight()/2) -i_height/2 );
	boxAmax.sety(i_positionA.gety()+(i_actorA.getBox()->GetHeight()/2) +i_height/2 );


	//previous position of boxB 
	Vector2 boxBcoordPre=Vector2(i_positionB.getx(),i_positionB.gety() );


	//checking distance and time with Xmax
	float TxEntry;
	{
		const Vector2 centre(boxAmax);
	    Vector2 normal(1,0);
		float distance=((centre- boxBcoordPre) * normal).getx();
		TxEntry=distance/(( boxBcoord-boxBcoordPre) * normal).getx();
	
	}

	//checking distance and time with Xmin
	float TxExit;
	{
		Vector2 centre(boxAmin);
	    Vector2 normal(1,0);
		float distance=((centre- boxBcoordPre) * normal).getx();
		TxExit=distance/((boxBcoord-boxBcoordPre) * normal).getx();
		
	}

	//checking distance and time with Ymax
	float TyEntry;
	{
		Vector2 centre(boxAmax);
	    Vector2 normal(0,1);
		float distance=((centre- boxBcoordPre) * normal).gety();
		TyEntry=distance/(( boxBcoord- boxBcoordPre) * normal).gety();
	
	}
	
	//checking distance and time with Ymin
	float TyExit;
	{
		Vector2 centre(boxAmin);
	    Vector2 normal(0,1);
		float distance=((centre- boxBcoordPre) * normal).gety();
		TyExit=distance/((boxBcoord-boxBcoordPre) * normal).gety();
		
	}

	

	if(TxEntry> TxExit)
	{
		float temp=TxExit;
		TxExit=TxEntry;
		TxEntry=temp;
		normalXSwaped=true;
	}


	if(TyEntry> TyExit)
	{
		float temp=TyExit;
		TyExit=TyEntry;
		TyEntry=temp;
		normalYSwaped=true;
		
	}

	if( (TxEntry>=0 && TxEntry<=1 && !isinf(TxEntry) )  ||
		(TyEntry>=0 && TyEntry<=1 && !isinf(TyEntry) ) 	
	  )
	{

	    if( (!isinf(TxEntry) && !isinf(TxExit) )  && (!isinf(TyEntry) && !isinf(TyExit) ) )
		{ 
			if( (TxEntry<=TyExit) && ( TyEntry<=TxExit) &&  TxEntry<=1 && TyEntry<=1) 
			{
					 collided=true;
			}
		   else 
			  collided=false;
		}
     

	}
	    //if both the boxes are stationary//special case
	 if( (isinf(TxEntry) || isinf(TxExit) )  && (isinf(TyEntry) || isinf(TyExit) ) )
		{
			if( ( boxBcoord.getx() >= boxAmin.getx() && boxBcoord.getx() <=boxAmax.getx() ) &&
				( boxBcoord.gety() >= boxAmin.gety() && boxBcoord.gety() <=boxAmax.gety() ) )
			      collided=true;
		        else 
			      collided=false;
		}

	   //If delta X is zero //special case
	 if( (isinf(TxEntry) || isinf(TxExit) )  && ( !isinf(TyEntry) && !isinf(TyExit) ) )
		{
			if( ( boxBcoord.getx() >= boxAmin.getx() && boxBcoord.getx() <=boxAmax.getx() ) && (TyEntry>=0 && TyEntry<=1 ) )
				   collided=true;
		        else 
			      collided=false;
		} 

	    //If delta Y is zero //special case
		if( (isinf(TyEntry) || isinf(TyExit) ) && ( !isinf(TxEntry) && !isinf(TxExit) ) ) 
		{
			if( (boxBcoord.gety() >= boxAmin.gety() && boxBcoord.gety() <=boxAmax.gety() ) && (TxEntry>=0 && TxEntry<=1 ) )
			       collided=true;
		        else 
			      collided=false;
		}


		if( (TyEntry<=0) && (TxEntry<=0) && (TxExit>=1) &&(TyExit>=1) )
				collided=true;

		 if(TxEntry>TyEntry)
			{
				if(normalXSwaped==true)
				  sideNormal=Vector3(-1.0,0.0,0.0);
				else
				  sideNormal=Vector3(1.0,0.0,0.0);
			}
			else
			{
			    if(normalYSwaped==true)
				  sideNormal=Vector3(0.0,-1.0,0.0);
				else
				  sideNormal=Vector3(0.0,1.0,0.0);
			}

	if(collided==true)
		return 1;


	else
		return 0;
}



}  //namespace end
