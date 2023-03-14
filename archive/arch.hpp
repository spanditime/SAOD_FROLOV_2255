#pragma once 
#include <string>

class Archive{
public:
	class exception{
	private:
		std::string desc;
		std::string wh;
		int exitcode;
	public:
		exception(std::string w, std::string d, int code);
		int getExitCode();
		std::string what();
		std::string descWhat();
	};

	static void decompress(const char* ifile, const char* ofile);
	static void compress(const char* ifile, const char* ofile);
};
