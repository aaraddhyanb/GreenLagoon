#ifndef _MATRIX_H
#define _MATRIX_H

#include<assert.h>
#include<vector>

namespace Engine{


	class Matrix
	{
	    private:
			unsigned int m_rows;
			unsigned int m_columns;
		    float	** m_matrix;

		public:

			inline Matrix();
			inline Matrix(unsigned int rows, unsigned int columns);
			inline void SetMatrix(float elements[],int length);
			inline void Transpose();
			inline int Size();
			inline void AddMatrix(Matrix &matrix);
			inline void SubtractMatrix(Matrix &matrix);
			inline Matrix* MultilpyByMatrix(Matrix &i_matrix);
			inline void MultiplyByVector(float vector[], int length);
			inline Matrix * Inverse();
			inline float ** getMatrix();
			inline ~Matrix();
	};

} //namespace end
	
#include"Matrix.inl"

#endif