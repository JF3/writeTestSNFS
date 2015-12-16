#include <string>
#include <mpi.h>
#include <fstream>
#include <iostream>
#include <vector>


char data (int pos)
{
	return 'A';
}


int main (int argc, char** argv)
{

	MPI_Init(&argc, &argv);

	int NProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &NProcs);

	int MyProc;
	MPI_Comm_rank(MPI_COMM_WORLD, &MyProc);

	if (MyProc == 0)
	{
		std::cout << "Running with " << NProcs << " processes." << std::endl;
	}

	std::string FullName = "testFile_D";
	int NFabs        = 32;
	int NBytesPerFab = 1024*1024;
	
	int filePos      = 0;

	for (int i = 0; i < NProcs; ++i)
	{
		if (MyProc == i)
		{
			std::cout << "Starting with proc " << i << std::endl;

			//taken from VisMF.H
			std::vector<char> io_buffer(40960 * 32);

			std::ofstream FabFile;
			//first arg taken from Array.H
	                FabFile.rdbuf()->pubsetbuf(io_buffer.data(), io_buffer.size());

			if (i == 0)
			{
				//
				// First set.
				//
				FabFile.open(FullName.c_str(),
						std::ios::out|std::ios::trunc|std::ios::binary);
			}
			else
			{
				FabFile.open(FullName.c_str(),
						std::ios::out|std::ios::app|std::ios::binary);
				//
				// Set to the end of the file.
				//
				FabFile.seekp(0, std::ios::end);
			}
			if (!FabFile.good())
			{
				std::cout << "File open failed" << std::endl;
				MPI_Finalize();
			}
	
			filePos = FabFile.tellp();

			//write out some stuff
			for (int j = 0; j < NFabs + 4*MyProc; j++)
			{
				FabFile << "FAB fake ()()()...\n";

				for (int k = 0; k < NBytesPerFab; k++)
				{
					FabFile << data(k);
				}
				// for convenience
				FabFile << "\n";
			}
			std::cout << "Current position in file: " << FabFile.tellp() << std::endl;

			FabFile.flush();

			FabFile.close();
			std::cout << "Done with proc " << i << std::endl;

			//pass token to the process with num
			int iBuff     = 0;
			int wakeUpPID = MyProc + 1;
			int tag       = 0;
			if (wakeUpPID < NProcs)
			{

				 MPI_Send(&iBuff,
						1,
						MPI_INT,
						wakeUpPID,
						tag,
						MPI_COMM_WORLD);

			}
		}

		if (MyProc == (i + 1))
		{
			//
			// Next set waits.
			//
			int iBuff;
			int waitForPID = MyProc - 1;
			int tag        = 0;
			MPI_Status stat;

			MPI_Recv(&iBuff,
					1,
					MPI_INT,
					waitForPID,
					tag,
					MPI_COMM_WORLD,
					&stat);
		}
	}

	std::vector<int> filePositions(NProcs);
	MPI_Gather(&filePos, 1, MPI_INT, filePositions.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (MyProc == 0)
	{
		std::ofstream headerfile;
		headerfile.open("testFile_H", std::ios::out|std::ios::trunc);
		headerfile << NProcs << std::endl;
//		for (int& fp : filePositions ) 
		for (int i = 0; i < filePositions.size(); i++)
		{
			headerfile << filePositions[i] << std::endl;
		}
		headerfile.close();

	}
	MPI_Finalize();

}


