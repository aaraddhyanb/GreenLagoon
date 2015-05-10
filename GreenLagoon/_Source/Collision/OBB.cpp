#include"OBB.h"


namespace Engine{

	bool OBB::collided=false;


bool OBB::CheckForCollision(Actor &i_actorA,Actor & i_actorB, float deltaTime)
{	
	collided=false;
	
	float rotation=i_actorA.getActorRotation();
	float mat1[]={ cos(rotation),sin(rotation),0.0,0.0,
		           -sin(rotation),cos(rotation),0.0,0.0,
				   0.0,0.0,1.0,0.0,
				   i_actorA.getActorPreviousPosition()->getx(), i_actorA.getActorPreviousPosition()->gety(),0.0,1.0
	             };
	Matrix *M_A_to_World=new Matrix(4,4);
	M_A_to_World->SetMatrix(mat1,16);

	Matrix *M_World_to_A=M_A_to_World->Inverse();

	delete M_A_to_World;

	float rotationB=i_actorB.getActorRotation();
	float mat2[]={ cos(rotationB),sin(rotationB),0.0,0.0,
		           -sin(rotationB),cos(rotationB),0.0,0.0,
				   0.0,0.0,1.0,0.0,
				  i_actorB.getActorPreviousPosition()->getx(), i_actorB.getActorPreviousPosition()->gety(),0.0,1.0
	           
	             };
	Matrix *M_B_to_World=new Matrix(4,4);
	M_B_to_World->SetMatrix(mat2,16);

	Matrix *M_World_to_B=M_B_to_World->Inverse();

	delete M_B_to_World;
	

	//Calculating position and velocity 
	//position of object B in Model space of A
	float mat5[]={i_actorB.getActorPreviousPosition()->getx(), i_actorB.getActorPreviousPosition()->gety(),0.0,1};
	Matrix *actorBposition=new Matrix(1,4);
	actorBposition->SetMatrix(mat5,4);

	Matrix *M_Bposition_in_A=actorBposition->MultilpyByMatrix(*M_World_to_A);

	//Dividing by xyz by w
	Vector3 BpositioninA=Vector3( M_Bposition_in_A->getMatrix()[0][0]/ M_Bposition_in_A->getMatrix()[0][3],
		                          M_Bposition_in_A->getMatrix()[0][1]/ M_Bposition_in_A->getMatrix()[0][3],
	                              M_Bposition_in_A->getMatrix()[0][2]/ M_Bposition_in_A->getMatrix()[0][3]);
	

	Matrix *M_Bposition_in_B=actorBposition->MultilpyByMatrix(*M_World_to_B);

	//Dividing by xyz by w
	Vector3 BpositioninB=Vector3( M_Bposition_in_B->getMatrix()[0][0]/ M_Bposition_in_B->getMatrix()[0][3],
		                          M_Bposition_in_B->getMatrix()[0][1]/ M_Bposition_in_B->getMatrix()[0][3],
	                              M_Bposition_in_B->getMatrix()[0][2]/ M_Bposition_in_B->getMatrix()[0][3]);

	delete actorBposition;
	delete M_Bposition_in_A;
	delete M_Bposition_in_B;

	//calculating velocity in model space of A
	float mat6[]={i_actorB.getActorPreviousVelocity()->getx(), i_actorB.getActorPreviousVelocity()->gety(), 0,0};
	Matrix *actorBvelocity=new Matrix(1,4);
	actorBvelocity->SetMatrix(mat6,4);

	Matrix *M_Bvelocity_in_A=actorBvelocity->MultilpyByMatrix(*M_World_to_A);

	//Dividing by xyz by w
	Vector3 BvelocityinA=Vector3( M_Bvelocity_in_A->getMatrix()[0][0],
		                          M_Bvelocity_in_A->getMatrix()[0][1],
	                              M_Bvelocity_in_A->getMatrix()[0][2]);

		
	Matrix *M_Bvelocity_in_B=actorBvelocity->MultilpyByMatrix(*M_World_to_B);

	//Dividing by xyz by w
	Vector3 BvelocityinB=Vector3( M_Bvelocity_in_B->getMatrix()[0][0],
		                          M_Bvelocity_in_B->getMatrix()[0][1],
	                              M_Bvelocity_in_B->getMatrix()[0][2]);

	delete actorBvelocity;
	delete M_Bvelocity_in_A;
	delete M_Bvelocity_in_B;

	//Calculating bounding box for object B
	float theta= i_actorA.getActorRotation()-i_actorB.getActorRotation();
	float widthOfB= (i_actorB.getBox()->GetWidth()*fabs(cos(theta)) ) + (i_actorB.getBox()->GetHeight()*fabs(sin( theta)) );
	float heightOfB= (i_actorB.getBox()->GetHeight()*fabs(cos(theta)) ) + (i_actorB.getBox()->GetWidth()*fabs(sin( theta)) );


	//position of object A in Model space of B
	float mat7[]={i_actorA.getActorPreviousPosition()->getx(), i_actorA.getActorPreviousPosition()->gety(), 0,1};
	Matrix *actorAposition=new Matrix(1,4);
	actorAposition->SetMatrix(mat7,4);

	Matrix *M_Aposition_in_B=actorAposition->MultilpyByMatrix(*M_World_to_B);

	//Dividing by xyz by w
	Vector3 ApositioninB=Vector3( M_Aposition_in_B->getMatrix()[0][0]/ M_Aposition_in_B->getMatrix()[0][3] ,
		                          M_Aposition_in_B->getMatrix()[0][1]/ M_Aposition_in_B->getMatrix()[0][3],
	                              M_Aposition_in_B->getMatrix()[0][2]/ M_Aposition_in_B->getMatrix()[0][3]);


	Matrix *M_Aposition_in_A=actorAposition->MultilpyByMatrix(*M_World_to_A);

	//Dividing by xyz by w
	Vector3 ApositioninA=Vector3( M_Aposition_in_A->getMatrix()[0][0]/ M_Aposition_in_A->getMatrix()[0][3],
		                          M_Aposition_in_A->getMatrix()[0][1]/ M_Aposition_in_A->getMatrix()[0][3],
	                              M_Aposition_in_A->getMatrix()[0][2]/ M_Aposition_in_A->getMatrix()[0][3]);


	delete actorAposition;
	delete M_Aposition_in_B;
	delete M_Aposition_in_A;


	//calculating velocity in model space of B
	float mat8[]={i_actorA.getActorPreviousVelocity()->getx(), i_actorA.getActorPreviousVelocity()->gety(), 0,0};
	Matrix *actorAvelocity=new Matrix(1,4);
	actorAvelocity->SetMatrix(mat8,4);

	Matrix *M_Avelocity_in_B=actorAvelocity->MultilpyByMatrix(*M_World_to_B);

	//Dividing by xyz by w
	Vector3 AvelocityinB=Vector3( M_Avelocity_in_B->getMatrix()[0][0],
		                          M_Avelocity_in_B->getMatrix()[0][1],
	                              M_Avelocity_in_B->getMatrix()[0][2]);



	Matrix *M_Avelocity_in_A=actorAvelocity->MultilpyByMatrix(*M_World_to_A);

	//Dividing by xyz by w
	Vector3 AvelocityinA=Vector3( M_Avelocity_in_A->getMatrix()[0][0],
		                          M_Avelocity_in_A->getMatrix()[0][1],
	                              M_Avelocity_in_A->getMatrix()[0][2]);

	delete actorAvelocity;
	delete M_Avelocity_in_B;
	delete M_Avelocity_in_A;
	delete M_World_to_B;
	delete M_World_to_A;

	
	//Calculating bounding box for object A
	float widthOfA= (i_actorA.getBox()->GetWidth()*fabs(cos(theta)) ) + (i_actorA.getBox()->GetHeight()*fabs(sin( theta)) );
	float heightOfA= (i_actorA.getBox()->GetHeight()*fabs(cos(theta)) ) + (i_actorA.getBox()->GetWidth()*fabs(sin( theta)) );

	bool firstCheck=false;
	bool secondCheck=false;

	firstCheck=AABB::CheckForCollision(i_actorB,BpositioninB,ApositioninB,BvelocityinB,AvelocityinB,widthOfA,heightOfA,deltaTime);
	Vector3 normal1=AABB::checkNormal();

	secondCheck=AABB::CheckForCollision(i_actorA,ApositioninA,BpositioninA,AvelocityinA,BvelocityinA,widthOfB,heightOfB,deltaTime);
	Vector3 normal2=AABB::checkNormal();

	float rotationA=i_actorA.getActorRotation();
	float matRotation[]={ cos(rotation),sin(rotation),0.0,
		                 -sin(rotation),cos(rotation),0.0,
				          0.0,0.0,1.0 
	                     };
	Matrix *M_Arotation=new Matrix(3,3);
	M_Arotation->SetMatrix(matRotation,9);

	float matAnormal[]={normal2.getx(), normal2.gety(), 0};
	Matrix *actorAnormal=new Matrix(1,3);
	actorAnormal->SetMatrix(matAnormal,3);

	Matrix *M_normal2=actorAnormal->MultilpyByMatrix(*M_Arotation);

	normal2=Vector3(M_normal2->getMatrix()[0][0],
	            	M_normal2->getMatrix()[0][1],
					M_normal2->getMatrix()[0][2]);

	delete M_Arotation;
	delete actorAnormal;
	delete M_normal2;

	//Multiplying the normal with rotation matrix 
	//calculating normal in world space
    float rotation_B=i_actorB.getActorRotation();
     float matRotation_B[]={ cos(rotation_B),sin(rotation_B),0.0,
		                 -sin(rotation_B),cos(rotation_B),0.0,
				          0.0,0.0,1.0 
	                     };
	Matrix *M_Brotation=new Matrix(3,3);
	M_Brotation->SetMatrix(matRotation_B,9);

	float matBnormal[]={normal2.getx(), normal2.gety(),0};
	Matrix *actorBnormal=new Matrix(1,3);
	actorBnormal->SetMatrix(matAnormal,3);

	Matrix *M_normal1=actorBnormal->MultilpyByMatrix(*M_Brotation);

	normal1=Vector3(M_normal1->getMatrix()[0][0],
	            	M_normal1->getMatrix()[0][1],
					M_normal1->getMatrix()[0][2]);

	delete M_Brotation;
	delete actorBnormal;
	delete M_normal1;

	if(firstCheck==true && secondCheck==true)
       {
		   OBB::collided=true;
		   //i_actorA.getBox()->getTrigger()->OnCollision(i_actorA);
		  // i_actorB.getBox()->getTrigger()->OnCollision(i_actorB);	   
	}

	return 0;
}


bool OBB::isCollided()
{
	return collided;
}


}  //namespace end
