#include"UnitTest.h"

using namespace Engine;

void UnitTest::MemoryPoolUnitTesting()
{
    
	printf("\n---------------Memory Pool Unit Test--------------------\n\n");


	 Vector3 *vector1=new Vector3(10.0f,10.0f,10.0f);
	 printf("\n\nVector1 at address:%d ->",(int)vector1);
	 vector1->display();

	 Vector3 *vector2=new Vector3(20.0f,20.0f,20.0f);
	 printf("\nVector2 at address:%d ->",(int)vector2);
	 vector2->display();
	

	 Vector3 *vector3=new Vector3(30.0f,30.0f,30.0f);
	 printf("\nVector3 at address:%d ->",(int)vector3);
	 vector3->display();

	 Vector3 *vector4=new Vector3(40.0f,40.0f,40.0f);
	 printf("\nVector4 at address:%d ->",(int)vector4);
	 vector4->display();


	  Vector3 *vector5=new Vector3(40.0f,40.0f,40.0f);
	 printf("\nVector5 at address:%d ->",(int)vector5);
	 vector5->display();

	  Vector3 *vector6=new Vector3(40.0f,40.0f,40.0f);
	 printf("\nVector6 at address:%d ->",(int)vector6);
	 vector6->display();

	  Vector3 *vector7=new Vector3(40.0f,40.0f,40.0f);
	 printf("\nVector7 at address:%d ->",(int)vector7);
	 vector7->display();


	  Vector3 *vector8=new Vector3(80.0f,40.0f,40.0f);
	 printf("\nVector8 at address:%d ->",(int)vector8);
	 vector8->display();


	  Vector3 *vector9=new Vector3(90.0f,40.0f,40.0f);
	 printf("\nVector9 at address:%d ->",(int)vector9);
	 vector9->display();

	  Vector3 *vector10=new Vector3(100.0f,40.0f,40.0f);
	 printf("\nVector10 at address:%d ->",(int)vector10);
	 vector10->display();

	  Vector3 *vector11=new Vector3(11.0f,11.0f,11.0f);
	 printf("\nVector11 at address:%d ->",(int)vector11);
	 vector11->display();

	

	  delete vector2;
	  printf("\nDeleted vector2\n");

	  
	  printf("\nVector1 at address:%d ->",(int)vector1);
	  vector1->display();

	  printf("\nVector3 at address:%d ->",(int)vector3);
	  vector3->display();

	   printf("\nVector4 at address:%d ->",(int)vector4);
	  vector4->display();

	  printf("\nVector5 at address:%d ->",(int)vector5);
	  vector5->display();

	  printf("\nVector6 at address:%d ->",(int)vector6);
	  vector6->display();

	  printf("\nVector7 at address:%d ->",(int)vector7);
	  vector7->display();

	  printf("\nVector8 at address:%d ->",(int)vector8);
	  vector8->display();

	  printf("\nVector9 at address:%d ->",(int)vector9);
	  vector9->display();

	  printf("\nVector10 at address:%d ->",(int)vector10);
	  vector10->display();


	 Vector3 *vector12=new Vector3(12.0f,12.0f,12.0f);
	 printf("\nVector12 at address:%d ->",(int)vector12);
	 vector12->display();

     Vector3 *vector13=new Vector3(13.0f,13.0f,13.0f);
	 printf("\nVector13 at address:%d ->",(int)vector13);
	 vector13->display();



}


void UnitTest::floatingNumbersComparison()
{
	//floating point comparison 
	// A part of assignment 6
	float a = 1.1f;
    float c = a * 0.2f;
    float d = a / 5.0f;
    assert( Engine::areRelativelyEqual( c, d ) == true );
	//this part of assignment6 ends here
	

}

void UnitTest::FastVectorUnitTesting()
{
    //object of FastVector3 statically created
	FastVector3 vecto;

	//check if cache aligned to 16
	assert(sizeof(vecto)==16);

	//check if sizeof the object is 16
	assert((int)&vecto%16==0);
	printf("\naddress of a member statically created: %d",(int)&vecto);
	


	 //Single Object
	FastVector3 *singleObject=new FastVector3();
	assert((int) singleObject % 16 == 0 );
	printf("\naddress of a member dynamically created: %d",(int)&singleObject);
	


	 
	 //Array of FastVector3 dynamically allocated by new
	FastVector3 *vec=new FastVector3[100];

	for(int i=0;i<100;i++)
	{
		//check if all the elements are allligned at CHACHE_LINE-16
	   assert( ((int)&vec[i]) % 16 == 0 );

	   //check if sizeof the object is 16
	   assert(sizeof(vec[i])==16);
	 
	   printf("\naddress of %dth element: %d",i,(int)&vec[i]);

	}

	delete singleObject;
	delete[] vec;

}

void UnitTest::MatrixTesting()
{
	
}