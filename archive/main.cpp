#include "arch.hpp"
#include <cstring>
#include <iostream>
#include <chrono>

void showHelpMessage(){
	std::cout<<"arch.out [options] [[arguments]]\n"<<
	"OPTIONS:\n\t-h --help\n\t\tshow this help message\n" <<
	"\t-d --decompress {input_filename} {output_filename}\n\t\t Decompress {input_filename} and save as {output_filename}\n"<<
	"\t-c --compress {input_filename} {output_filename}\n\t\t Compress {input_filename} and save as {output_filename}\n" <<
	"EXAMPLE:\n\tarch.out -d a.txt a.compressed\n" <<
	"INFO:\n"<<
	"This application is developed as an educational project in University Dubna by Eugene Frolov(spanditime on GitHub), and is used to archive and dearchive files\n";
}

void printInvalidArgumentsCountErrorDCAndExit(int argcount,const char*option){
	std::cout<< "Error: ";
	if( argcount > 2){
		std::cout << "Too many ";
	} else {
		std::cout<< "Not enough ";
	}
	std::cout<< "arguments for "<< option << " option\nDescription: Expected 2 arguments, got " << argcount<< "\n";
	showHelpMessage();
	exit(3);
}

int main(int argc, char **argv){
	if(argc < 2){
		std::cout << "Error: No options provided\n";
		showHelpMessage();
		exit(1);
	}
	if(!std::strcmp("-h",argv[1]) || !std::strcmp("--help", argv[1])){
		int exit_code = 0;
		if(argc != 2){
			std::cout << "Error: Too many arguments for "<< argv[1] <<" option\nDescription: Option " << argv[1] << " doesn't takes any additional arguments\n";
			exit_code = 2;
		}
		showHelpMessage();
		exit(exit_code);
	}
	if(!std::strcmp("-d",argv[1]) || !std::strcmp("--decompress", argv[1])){
		if(argc != 4){
			printInvalidArgumentsCountErrorDCAndExit(argc - 2,argv[1]);
		}
		try{
			auto time_one = std::chrono::steady_clock::now();
			Archive::decompress(argv[2], argv[3]);
			auto time_two = std::chrono::steady_clock::now();
			std::cout<<"Done!\nTime elapsed: "<< std::chrono::duration_cast<std::chrono::microseconds>(time_two - time_one).count()/1e6 << " sec\n";
		}catch(Archive::exception exc){
			std::cout<< "Error: " << exc.what() << "\nDescription: " << exc.descWhat()<< "\n";
			exit(exc.getExitCode());
		}
		return 0;
	}
	if(!std::strcmp("-c",argv[1]) || !std::strcmp("--compress", argv[1])){
		if(argc != 4){
			printInvalidArgumentsCountErrorDCAndExit(argc - 2,argv[1]);
		}
		try{
			auto time_one = std::chrono::steady_clock::now();
			Archive::compress(argv[2], argv[3]);
			auto time_two = std::chrono::steady_clock::now();
			std::cout<<"Done!\nTime elapsed: "<< std::chrono::duration_cast<std::chrono::microseconds>(time_two - time_one).count()/1e6 << " sec\n";
		}catch(Archive::exception exc){
			std::cout<< "Error: " << exc.what() << "\nDescription: " << exc.descWhat()<< "\n";
			exit(exc.getExitCode());
		}
		return 0;
	}
	std::cout<< "Error: Invalid option " << argv[1] << std::endl;
	showHelpMessage();
	exit(1);
}
