#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include<fstream>
#include<unistd.h>
#include<time.h>
#include<stdio.h>

#define MAXNAME 21

using namespace std;

struct cord
{
    double x;
    double y;
    char name[MAXNAME];
};

void validateString(string &str)
{
    string res = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            if (i == 0 || i == str.length()-1) continue;
            if (str[i-1] != ' ') res = res + str[i];
            continue;
        }
        res = res + str[i];
    }
    str = res;
}

void convertStringToCharArray(string str, char arr[])
{
   
    for (int i = 0; i < str.length(); i++)
    {
        arr[i] = str[i];
    }
    arr[str.length()] = '\0';
    return;
}



void randomLocation(cord* &location)
{
    srand(time(NULL));
    int x = rand()%(233925050-85624409) + 85624409;
    int y = rand()%(1094616339-1021439400) + 1021439400;

    location->x = (double)x/10000000;
    location->y = (double)y/10000000;

    cout << location->x << "," << location->y << endl;
}
void simulateRunning(cord* &location)
{
    srandom(time(NULL));
    int x = rand()%20001-10000;
    int y = rand()%20001-10000;

    location->x = location->x + (double)x/10000000;
    location->y = location->y + (double)y/10000000;

    cout << location->x << "," << location->y << endl;
}
