//David Wang
//CSE 140 Project 3
//Collab w/ Stan Lin


//Unrolling 

void dgemm(int m, int n, float *A, float *C)
{
	for(int x = 0; x < m; x++)
	{
		for(int z = 0; z < n; z++)
		{
			for(int y = 0; y < m; y++)
			{
				if(m % 2 == 0) //prevent breaks
				{
					C[x + y * m] += A[x + z * m] * A[y + z * m];
					C[x + (y + 1) * m] += A[x + z * m] * A[(y + 1) + z * m];
					//C[x + (y + 2) * m] += A[x + z * m] * A[(y + 2) + z * m];
					//C[x + (y + 3) * m] += A[x + z * m] * A[(y + 3) + z * m];
					y++;
				}
				else
				{
					C[x + y * m] += A[x + z * m] * A[y + z * m];
				}
			}
		}
	}
 }


// 	Transposing

// void dgemm(int m, int n, float *A, float *C)
// {
// 	for(int y = 0; y < m; y++)
// 	{
// 		for(int z = 0; z < n; z++)
// 		{
// 			for(int x = 0; x < m; x++)
// 			{
// 				C[x + y * m] += A[x + z * m] * A[y + z * m];
// 			}
// 		}
// 	}
// }

// //Blocking

// void dgemm(int m, int n, float *A, float *C)
// {

// 	int size = m; //blocksize

// 	for(int x = 0; x < m; x+= size)
// 	{
// 		for(int y = 0; y < m; y+= size)
// 		{
// 			for(int z = 0; z < m; z+= size)
// 			{
// 				for(int yy = 0; yy < size; yy++)
// 				{
// 					for(int zz = 0; zz < n; zz++)
// 					{
// 						for(int xx = 0; xx < size; xx++)
// 						{
// 							C[(x + xx) + (y  + yy) * m] += A[(x + xx) + (z + zz) * m] * A[(y + yy) + (z + zz) * m];
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }


