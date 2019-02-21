#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "validData.h"
#include "DataWriter.h"
using namespace std;
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
   DataWriter w;
   vector<double> c = {1.0, 0.3, 0.8, 1.5, 0.7, 1.9, 0.7, 0.12345, 0.663};
   vector<pair<double, double> >pts = {{0,0}, {1,0}, {1,1}, {0,1}, {0,0}, {1,0}, {1,1}, {0,1}, {1,1}};
   const char * fn = "output";
   w.write(c, pts, fn);
}
