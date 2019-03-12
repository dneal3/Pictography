#ifndef VALIDATEDATA_H
#define VALIDATEDATA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Create a ValidData class
// Stores defines as privates
// Stores string as private
// public function: Validate data - returns bool

class ValidData
{
   public:
      ValidData(std::string s)   { data = s; };
      void PrintData()           { printf("ValidData's data: %s\n", data.c_str()); };
      bool ValidateData();
	int GetMaxChars(){return max_chars;}

   private:
      std::string data;
      int max_chars = 999;
      int min_chars = 1;
      int max_ascii = 126;
      int min_ascii = 32;
};
bool ValidData::ValidateData()
{
   // If the length of the data is too small, then data is invalid
   if (data.length() < min_chars)
   {
      printf("Message had %lu characters. Quitting now.\n", data.length());
      return false;
   }

   // If the length of the data is too big, then data is invalid
   if (data.length() > max_chars)
   {
      printf("Message had %lu characters. Quitting now.\n", data.length());
      return false;
   }

   // Check each of the ASCII values of the message
   for (int i = 0; i < data.length(); i++)
   {
      // If the ASCII value is too big, then data is invalid
      if (data[i] > max_ascii)
      {
         printf("A character is too large of an ASCII value. Quitting now.\n");
         return false;
      }

      // If the ASCII value is too small, then data is invalid
      if (data[i] < min_ascii)
      {
         printf("A character is too small of an ASCII value. Quitting now.\n");
         return false;
      }
   }

   return true;
}
#endif
