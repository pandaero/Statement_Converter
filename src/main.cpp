#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int	main()
{
	// Ask for input folder
	std::cout << "CONVERTIDOR CARTOLAS BANCO DE CHILE" << std::endl;
	std::cout << "para convertir archivos de .txt a .csv (Excel)" << std::endl << std::endl;
	std::cout << "Definir carpeta con archivos .txt: ";

	std::string	path;
	std::getline(std::cin, path);
	std::set<std::string>	files;

	for (auto & entry : fs::directory_iterator(path))
		files.insert(entry.path());

	std::cout << "Los siguientes archivos se convertiran:" << std::endl;
	for (std::set<std::string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << *it << std::endl;

	std::string	buffer;
	std::cout << "Continuar? (Enter)";
	std::getline(std::cin, buffer);

	for (std::set<std::string>::iterator it = files.begin(); it != files.end(); ++it)
	{
		std::cout << "Abriendo archivo: " << *it << std::endl;
		std::fstream	file(*it);
		if (file.fail())
		{
			std::cerr << "No se pudo abrir el archivo: " << *it << std::endl;
			continue;
		}

		std::vector<std::string>	fileOutput;
		std::string	fileBuffer;
		int	i = 0;
		while (getline(file, fileBuffer))
		{
			if (i == 0)
				fileOutput.push_back(fileBuffer);
			else
			{
				std::string	clean(fileBuffer);
				clean.erase(remove(clean.begin(), clean.end(), '\"'), clean.end());
				fileOutput.push_back(clean);
			}
			++i;
		}
		file.close();

		std::string		outFileName(*it);

		outFileName.replace(outFileName.size() - 3, 3, "csv");
		outFileName.replace(0, path.size(), "output");

		std::fstream	outFile(outFileName, std::fstream::out);
		if (outFile.fail())
		{
			std::cerr << "No se pudo crear el archivo: " << outFileName << std::endl;
			continue;
		}

		for (auto it = fileOutput.begin(); it != fileOutput.end(); ++it)
			outFile << *it << '\n';
		outFile << "\r\n";
		outFile.close();
	}

	return (0);
}
