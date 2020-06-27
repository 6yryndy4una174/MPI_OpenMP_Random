#include <iostream>
#include <ctime>
#include <string>
#include <mpi.h>
#include <omp.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);
	int seed = (int)time(0);
	srand(time(0));
	int p_rank, t_rank, total;
	MPI_Comm_size(MPI_COMM_WORLD, &total);
	MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
	std::cout << "Total process: " << total << std::endl;
#pragma omp parallel num_threads(4) private(t_rank)
	{
#pragma omp critical 
		{
			t_rank = omp_get_thread_num();
			srand(seed * 123 + (t_rank + 132) * 321 + (p_rank + 321) * 132);
			int num = rand();
			std::cout << "I am " << t_rank << " thread from " << p_rank << " process, my random number = " << num << std::endl;
		}
	}
	MPI_Finalize();
}