#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
   // Let the user know about the message "requirements"
   cout << "Input a message between 1 and 1023 characters (excluding enter command).\n";
   cout << "Characters should have an ASCII value between 32 and 126.\n";
   cout << "Input message to encrypt:\n";

   // Get the user's message
   string message;
   getline(cin, message);

   // While loop to check if message's length is bigger than 0 and if message's ASCII values are within range
   while (true)
   {
      // While the input length is 0, ask the user for a new message
      while (message.length() == 0)
      {
         cout << "You entered 0 charaters. Try again:\n";
         getline(cin, message);
      }

      // Boolean variable that will determine if another check of the message is required
      // If it's value is 1 at the end of the loop, the while loop will start again
      // Otherwise, the input is validated
      bool check_again = 0;

      // Check each of the ASCII values of the message
      for (int i = 0; i < message.length(); i++)
      {
         // If the ASCII value is out of bounds, another check of the message is required
         if (message[i] < 32 || message[i] > 126)
         {
            cout << "You entered a character under 32 or above 126. Try again:\n";
            getline(cin, message);
            check_again = 1;
         }
         // If another check of the message is required, break out of for loop
         if (check_again)
         {
            break;
         }
      }
      // If there isn't another check of the message, break out of while loop
      if (!check_again)
      {
         break;
      }
   }

   // Output the validated message
   cout << "\nYou entered:\n" << message << "\n";
}
