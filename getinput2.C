#include <iostream>
#include <stdio.h>
#include <string>

#define MAX_CHARS 1024
#define MIN_CHARS 1
#define MAX_ASCII 126
#define MIN_ASCII 32

int main()
{
   // Get the user's message
   std::string message;
   getline(std::cin, message);

   // If the length of the message is too small, then quit the program
   if (message.length() < MIN_CHARS)
   {
      printf("Message had %lu characters. Quitting now.\n", message.length());
      return 0;
   }

   // If the length of the message is too big, then quit the program
   if (message.length() > MAX_CHARS)
   {
      printf("Message had %lu characters. Quitting now.\n", message.length());
      return 0;
   }

   // Check each of the ASCII values of the message
   for (int i = 0; i < message.length(); i++)
   {
      // If the ASCII value is too big, then quit the program
      if (message[i] > MAX_ASCII)
      {
         printf("%c is too large of an ASCII value. Quitting now.\n", message[i]);
         return 0;
      }

      // If the ASCII value is too small, then quit the program
      if (message[i] < MIN_ASCII)
      {
         printf("%c is too small of an ASCII value. Quitting now.\n", message[i]);
         return 0;
      }
   }

   printf("Message received was: %s\n", message.c_str());
}
