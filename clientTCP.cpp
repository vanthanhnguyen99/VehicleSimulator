#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "structs.h"
#include<stdio.h>

#define MAXHOSTNAME 256

using namespace std;


int main()
{
   struct sockaddr_in remoteSocketInfo;
   struct hostent *hPtr;
   int socketHandle;
   const char *remoteHost= "192.168.1.8";
   int portNumber = 8083;
   bzero(&remoteSocketInfo, sizeof(sockaddr_in));  // Clear structure memory

   // Get system information

   if((hPtr = gethostbyname(remoteHost)) == NULL)
   {
      cerr << "System DNS name resolution not configured properly." << endl;
      cerr << "Error number: " << ECONNREFUSED << endl;
      exit(EXIT_FAILURE);
   }

   // create socket

   if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      close(socketHandle);
      exit(EXIT_FAILURE);
   }

   // Load system information into socket data structures

   memcpy((char *)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
   remoteSocketInfo.sin_family = AF_INET;
   remoteSocketInfo.sin_port = htons((u_short)portNumber);      // Set port number

   if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0)
   {
      close(socketHandle);
      exit(EXIT_FAILURE);
   }

   int rc = 0;  // Actual number of bytes read by function read()
   int x;
   cout << "Size = " << sizeof(x) << endl;
   bool *p = new bool;
   recv(socketHandle,p,sizeof(bool),0);

   if (*p)
   {
      int *type = new int;
      *type = 1;
      send(socketHandle,type,sizeof(int),0);
      cout << "Server accepted" << endl;
      delete type;
   }
   else
   {
      cout << "Server not accepted";
      close(socketHandle);
      return 0;
   }

   cord *value = new cord;

   // send name and check
   bool *check = new bool;
   string deviceName = "";
   cout << "Enter your device's name: ";
   getline(cin,deviceName);
   validateString(deviceName);

   convertStringToCharArray(deviceName,value->name);
   value->x = -1.0;
   value->y = -1.0;
   send(socketHandle,value,sizeof(cord),0);
   recv(socketHandle,check,sizeof(bool),0);
   while (deviceName.length() > 20 || deviceName.length() == 0 || !*check)
   {
      if (*check) cout << "Please enter less than 20 characters and not empty" << endl;
      else cout << "Duplicate name, retry!" << endl;
      cout << "Enter your device's name: ";
      getline(cin,deviceName);
      validateString(deviceName);

      convertStringToCharArray(deviceName,value->name);
      value->x = -1.0;
      value->y = -1.0;
      send(socketHandle,value,sizeof(cord),0);
      recv(socketHandle,check,sizeof(bool),0);
   }
   delete check;
   
   convertStringToCharArray(deviceName,value->name);
   randomLocation(value);
   send(socketHandle,value,sizeof(cord),0);
   while (*p)
   {
      simulateRunning(value);
      // cout << (float) (value->x) << "," <<(float) (value->y) << endl;
      send(socketHandle,value,sizeof(cord),0);
      sleep(2);
   }
   close(socketHandle);
}
