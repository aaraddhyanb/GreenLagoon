#include"util.h"

using namespace std;

Engine::Matrix::Matrix():
m_rows(0),
m_columns(0)
{

}


Engine::Matrix::Matrix(unsigned int i_rows, unsigned int i_columns):
m_rows(i_rows),
m_columns(i_columns),
m_matrix(0)
{
	m_matrix= new float*[i_rows];

	for(unsigned int i=0; i<i_rows;i++)
	{
		m_matrix[i]=new float [i_columns];
	}
}


void Engine::Matrix::SetMatrix(float elements[], int i_length)
{
	assert(elements);
	assert(m_matrix);
	
	assert(this->Size()==i_length);

	unsigned int l=0;

	for(unsigned int i=0;i< m_rows;i++)
		for(unsigned int j=0;j<m_columns;j++)
		{
			
				m_matrix[i][j]=elements[l];
				l++;
		}

}

void Engine::Matrix::Transpose()
{
	assert(m_matrix);

	unsigned int oldRows=m_rows;
	unsigned int oldColumns=m_columns;
	
	m_rows=oldColumns;
	m_columns=oldRows;

	float **newMatrix;
	newMatrix=new float*[m_rows];
	for(unsigned int i=0;i<m_rows;i++)
		newMatrix[i]=new float[m_columns];
	 
	for(unsigned int i=0;i<oldRows;i++)
		for(unsigned int j=0;j<oldColumns;j++)
		{
			newMatrix[j][i]=m_matrix[i][j];	
		}

	for(unsigned int i=0;i<oldRows;i++)
		delete [] m_matrix[i];
	    delete [] m_matrix;

	//New Transpose matrix
	m_matrix=newMatrix;
	
}

void Engine::Matrix::AddMatrix(Matrix &i_matrix)
{
	assert(this->m_rows==i_matrix.m_rows);
	assert(this->m_columns==i_matrix.m_columns);

	for(unsigned int i=0;i<m_rows;i++)
		for(unsigned int j=0;j<m_columns;j++)
		{
			this->m_matrix[i][j]+=i_matrix.m_matrix[i][j];
		}

}

void Engine::Matrix::SubtractMatrix(Matrix &i_matrix)
{
	assert(this->m_rows==i_matrix.m_rows);
	assert(this->m_columns==i_matrix.m_columns);

	for(unsigned int i=0;i<m_rows;i++)
		for(unsigned int j=0;j<m_columns;j++)
		{
			this->m_matrix[i][j]-=i_matrix.m_matrix[i][j];
		}

}

Engine::Matrix *  Engine::Matrix::MultilpyByMatrix(Matrix &i_matrix)
{
	assert(this->m_columns==i_matrix.m_rows);

	Matrix *newMatrix=new Matrix(this->m_rows, i_matrix.m_columns);

	float tempValue=0;

	for(unsigned int i=0;i< this->m_rows;i++)
	{
		for(unsigned int k=0;k<i_matrix.m_columns;k++)
		{
			for(unsigned int j=0;j< i_matrix.m_rows;j++)
			{
				tempValue+=(this->m_matrix[i][j] * i_matrix.m_matrix[j][k]); 
			}

			newMatrix->m_matrix[i][k]=tempValue;
			tempValue=0;
		}
	}

   return newMatrix;
}



Engine::Matrix *  Engine::Matrix::Inverse()
{
	
	float mat[]={ this->m_matrix[0][0], this->m_matrix[0][1],this->m_matrix[0][2],
		          this->m_matrix[1][0],this->m_matrix[1][1],this->m_matrix[1][2],
				  this->m_matrix[2][0],this->m_matrix[2][1],this->m_matrix[2][2],
	          };
	Matrix *newMatrix=new Matrix(3,3);
	newMatrix->SetMatrix(mat,9);

	//Taking the transpose of rotation matrix
	newMatrix->Transpose();

	//Negate the translation of the matrix
	float mat2[]={ -(this->m_matrix[3][0]), -(this->m_matrix[3][1]), -(this->m_matrix[3][2]) };
    Matrix *translation=new Matrix(1,3);
	translation->SetMatrix(mat2,3);
    
	Matrix *lastColumn=translation->MultilpyByMatrix(*newMatrix);

	float mat3[]={newMatrix->m_matrix[0][0],newMatrix->m_matrix[0][1],newMatrix->m_matrix[0][2], 0,
		          newMatrix->m_matrix[1][0],newMatrix->m_matrix[1][1],newMatrix->m_matrix[1][2], 0,
				  newMatrix->m_matrix[2][0],newMatrix->m_matrix[2][1],newMatrix->m_matrix[2][2], 0,
				  lastColumn->m_matrix[0][0],lastColumn->m_matrix[0][1],lastColumn->m_matrix[0][2], 1
	          };
   
    Matrix *inverseMatrix=new Matrix(4,4);
	inverseMatrix->SetMatrix(mat3,16);
    
	delete newMatrix; 
	delete translation;
	delete lastColumn;

	return inverseMatrix;
}


int Engine::Matrix::Size()
{
	assert(m_rows>0);
	assert(m_columns>0);

	return (m_rows*m_columns);
}


float ** Engine::Matrix::getMatrix()
{
	
	return m_matrix;
}

Engine::Matrix::~Matrix()
{
	assert(m_matrix);

	for(unsigned int i=0;i<m_rows;i++)
		delete [] m_matrix[i];
	    delete [] m_matrix;

		m_matrix=NULL;
		m_rows=0;
		m_columns=0;
}