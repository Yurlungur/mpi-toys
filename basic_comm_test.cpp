/*
 * basic_comm_test.cpp
 * Author: Jonah Miller (jonah.maxwell.miller@gmail.com)
 * Time-stamp: <2017-02-21 15:25:56 (jmiller)>
 *
 * This is a small script to test how the MPI infrastructure is
 * working. We perform An MPI broadcast, reduce, and ask each
 * MPI-thread for its rank and host name.
 */

#include <string>
#include <stdio.h>
#include <mpi.h>
#include <cstdlib>

const int HEAD = 0;

int main(int argc, char **argv) {
  int rank, size;
  int hostname_size;
  std::string hostname;
  hostname.resize(MPI_MAX_PROCESSOR_NAME);

  // MPI Init
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  // Get MPI hostname
  MPI_Get_processor_name(&(hostname[0]),
			 &hostname_size);
  hostname.resize(hostname_size);

  // Welcome message
  if (rank == HEAD) {
    printf("Welcome to the MPI test program!\n");
    printf("Now each rank will say hello.\n");
  }
  // In realistic programs, avoid barrier as much as possible!
  MPI_Barrier(MPI_COMM_WORLD);

  // Output hello
  printf("\tHello from %s: rank %d of %d.\n",
	 hostname.data(),rank,size-1);
  // In realistic programs, avoid barrier as much as possible!

  // Test communication
  int to_sum = 1;
  int total = 0;
  int expected_total = to_sum*size;
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank == HEAD) {
    printf("Now performing reduce operation.\n");
    printf("We will sum up the integer %d over all ranks.\n",
	   to_sum);
    printf("So the result of the reduce operation should be %d\n",
	   expected_total);
    printf("...Reducing...\n");
  }
  MPI_Reduce(&to_sum,&total,1,MPI_INT,MPI_SUM,HEAD,MPI_COMM_WORLD);
  if (rank == HEAD) {
    printf("Reduction complete!\n");
    printf("\tWe got: %d\n\tWe should have gotten: %d.\n",
	   total,expected_total);
    printf("All done. Signing off.\n");
  }
  
  MPI_Finalize();
  return EXIT_SUCCESS;
}
