#include <string>
#include <fstream>
#include <iostream>
#include <vector>


int main (void)
{
	std::ifstream header;
	std::ifstream data;
	
	std::string file("testFile");

	header.open(std::string(file+"_H").c_str(), std::ios::in);
	data.open(std::string(file+"_D").c_str(), std::ios::in);

	int nPos;
	header >> nPos;
	for (int i = 0; i < nPos; i++)
	{
		int fp;
		char c;
		header >> fp;

		data.seekg(fp, std::ios::beg); 

		std::cout << "Seeking to " << fp << std::endl;
		data >> c;
		if (c != 'F') std::cout << "Expected \'F\', got " << c << std::endl;
		data >> c;
		if (c != 'A') std::cout << "Expected \'A\', got " << c << std::endl;
		data >> c;
		if (c != 'B') std::cout << "Expected \'B\', got " << c << std::endl;
	}
	

	header.close();
	data.close();

	

}
