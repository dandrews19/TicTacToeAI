#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <fstream>
#include <string>
#include <cstdlib>

// Name: 
//		CheckTextFilesSame
// Input:
//		1. The first file name to check
//		2. The second file name to check
// Output: 
//		Boolean -- true indicates files are the same
// Side effects: 
//		Creates system command (based on host OS) and runs system command to check files
// Summary:
//		Uses system native command to check for differences between 2 files
//		Uses C++ #defines to determine host OS
bool CheckTextFilesSame(const std::string& fileNameA, const std::string& fileNameB)
{
	// This is super unfortunate that I'm using std::system, but...
	std::string command;

#ifdef _MSC_VER
	// Windows version needs to fix separators on 1st input (so forward slash becomes backslash)
	std::string temp = fileNameA;
	std::replace(temp.begin(), temp.end(), '/', '\\');
	command = "FC /W /LB5 " + temp + " " + fileNameB;

#elif __APPLE__
	// Mac version needs no change
	command = "diff -sBbu " + fileNameA + " " + fileNameB + " > diff.txt";

#else
	// Linux version, just in case the Mac one becomes different
	command = "diff -sBbu " + fileNameA + " " + fileNameB + " > diff.txt";
#endif

	// Run the command we just constructed
	int retVal = std::system(command.c_str());

#if !defined(_MSC_VER)
   // Non Windows needs to add up to 50 lines of diff output, so we know the difference
    std::system("echo \"***DIFFERENCES***\"");
   std::system("head -50 diff.txt");
#endif

   // If there were 0 differences, indicate true
	return retVal == 0;
}
