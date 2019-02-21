#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "validData.h"

int main()
{
   // Get the user's message
   std::string message;
   getline(std::cin, message);
   printf("Message received: %s\n", message.c_str());

   // Create instance on data
   ValidData data(message);

   // Check if message was successfully copied over
   data.PrintData();

   // Check if data is valid
   if (data.ValidateData() == true)
   {
      printf("Data is valid\n");
   }
   else
   {
      printf("Data is invalid\n");
   }
}
