/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef cmSystemTools_h
#define cmSystemTools_h

#include "cmStandardIncludes.h"

/** \class cmSystemTools
 * \brief A collection of useful functions for CMake.
 *
 * cmSystemTools is a class that provides helper functions
 * for the CMake build system.
 */
class cmSystemTools
{
public:
  /**
   * Make a new directory if it is not there.  This function
   * can make a full path even if none of the directories existed
   * prior to calling this function.  
   */
  static bool MakeDirectory(const char* path);

  /**
   * Replace replace all occurances of the string in
   * the source string.
   */
  static void ReplaceString(std::string& source,
                            const char* replace,
                            const char* with);

  /**
   * Look for and replace registry values in a string
   */
  static void ExpandRegistryValues(std::string& source);

  /**
   * make sure on windows that paths with // are converted to \\
   */
  static std::string HandleNetworkPaths(const char*);

  /**
   * Return a string equivalent to the input string, but with all " " replaced
   * with "\ " to escape the spaces.
   */
  static std::string EscapeSpaces(const char*);
  
  /**
   * Return a string equivalent to the input string, but with all " replaced
   * with \"  to escape the quote
   */
  static std::string EscapeQuotes(const char*);

  /**
   * Return a capitalized string (i.e the first letter is uppercased, all other
   * are lowercased).
   */
  static std::string Capitalized(const std::string&);
  
  /**
   * Return a lower case string
   */
  static std::string LowerCase(const std::string&);
  
  /**
   * Replace Windows file system slashes with Unix-style slashes.
   */
  static const char *ConvertToUnixSlashes(std::string& path);

  /**
   * Replace Unix file system slashes with Windows-style slashes
   */
  static const char *ConvertToWindowsSlashes(std::string& path);

  /**
   * Replace Unix file system slashes with Windows-style slashes and
   * remove any duplicate \\ slashes to clean the path.
   */
  static const char *ConvertToWindowsSlashesAndCleanUp(std::string& path);

  ///! Return true if a file exists in the current directory.
  static bool FileExists(const char* filename);

  /**
   * Read a CMake command (or function) from an input file.  This
   * returns the name of the function and a list of its 
   * arguments.
   */
  static bool ParseFunction(std::ifstream&, 
                            std::string& name,
                            std::vector<std::string>& arguments);

  /**
   *  Extract white-space separated arguments from a string.
   *  Double quoted strings are accepted with spaces.
   *  This is called by ParseFunction.
   */
  static void GetArguments(std::string& line,
                           std::vector<std::string>& arguments);
  
  /**
   * Given a string, replace any escape sequences with the corresponding
   * characters.
   */
  static std::string RemoveEscapes(const char*);
  

  /**
   *  Add the paths from the environment variable PATH to the 
   *  string vector passed in.
   */
  static void GetPath(std::vector<std::string>& path);

  /**
   *  Get the file extension (including ".") needed for an executable
   *  on the current platform ("" for unix, ".exe" for Windows).
   */
  static const char* GetExecutableExtension();
  
  /**
   * Display an error message.
   */
  static void Error(const char* m, const char* m2=0,
                    const char* m3=0, const char* m4=0);

  /**
   * Display a message.
   */
  static void Message(const char* m, const char* title=0);

  ///! Return true if there was an error at any point.
  static bool GetErrorOccuredFlag() 
    {
      return cmSystemTools::s_ErrorOccured;
    }

  ///! Set the error occured flag back to false
  static void ResetErrorOccuredFlag()
    {
      cmSystemTools::s_ErrorOccured = false;
    }
  
  /**
   * Copy the source file to the destination file only
   * if the two files differ.  
   */
  static void CopyFileIfDifferent(const char* source,
                                  const char* destination);
  
  ///! Compare the contents of two files.  Return true if different.
  static bool FilesDiffer(const char* source,
                          const char* destination);
  ///! Copy a file.
  static void cmCopyFile(const char* source,
                       const char* destination);
  
  ///! Remove a file.
  static void RemoveFile(const char* source);
  
  /** 
   * does a string indicate a true or on value ? This is not the same
   * as ifdef. 
   */ 
  static bool IsOn(const char* val);
  
  /** 
   * does a string indicate a false or off value ? Note that this is
   * not the same as !IsOn(...) because there are a number of
   * ambiguous values such as "/usr/local/bin" a path will result in
   * IsON and IsOff both returning false. Note that the special path
   * NOTFOUND or IGNORE will cause IsOff to return true. 
   */
  static bool IsOff(const char* val);

  ///! Find a file in the system PATH, with optional extra paths.
  static std::string FindFile(const char* name,
				 const std::vector<std::string>& path= std::vector<std::string>());

  ///! Find an executable in the system PATH, with optional extra paths.
  static std::string FindProgram(const char* name,
				 const std::vector<std::string>& path= std::vector<std::string>());

  ///! Find a library in the system PATH, with optional extra paths.
  static std::string FindLibrary(const char* name,
				 const std::vector<std::string>& path);

  ///! return true if the file is a directory.
  static bool FileIsDirectory(const char* name);
  static void Glob(const char *directory, const char *regexp,
                   std::vector<std::string>& files);
  
  static std::string GetCurrentWorkingDirectory();
  static std::string GetProgramPath(const char*);
  static void SplitProgramPath(const char* in_name, 
                               std::string& dir, 
                               std::string& file);
  static std::string CollapseFullPath(const char*);

  ///! return path of a full filename (no trailing slashes).
  static std::string GetFilenamePath(const std::string&);
  
  ///! return file name of a full filename (i.e. file name without path).
  static std::string GetFilenameName(const std::string&);
  
  ///! return file extension of a full filename (dot included).
  static std::string GetFilenameExtension(const std::string&);
  static std::string GetFilenameShortestExtension(const std::string&);
  
  ///! return file name without extension of a full filename.
  static std::string GetFilenameNameWithoutExtension(const std::string&);
  
  static long int ModifiedTime(const char* filename);

  /**
   * Run an executable command and put the stdout in output.
   * A temporary file is created in the binaryDir for storing the
   * output because windows does not have popen.
   *
   * If verbose is false, no user-viewable output from the program
   * being run will be generated.
   */
  static bool RunCommand(const char* command, std::string& output,
                         bool verbose = true);
  static bool RunCommand(const char* command, std::string& output,
                         int &retVal, bool verbose = true);
  
  ///! Generate a temporary file name
  static std::string TemporaryFileName();

  ///! change directory the the directory specified
  static int ChangeDirectory(const char* dir);
    
private:
  static bool s_ErrorOccured;
};


#endif
