//
//  main.cpp
//  syntax1
//
//  Created by Vincewang on 10/4/14.
//  Copyright (c) 2014 Vincewang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

list<string>::iterator it;
list<string> tokenlist;

list<string> stringtoken(string input)
{
    list<string> strlist;
    istringstream iss(input);
    string temp;
    while (iss >> temp){
        strlist.push_back(temp);
    }
    return strlist;
}

bool StrPlus(string input){
    return (input == "+");
}

bool StrNumeric(string input){
    if (input == "0")
        return true;
    else
        if (input[0] == '0')
            return false;
        else{
            for (char c : input){
                if (!isdigit(c))
                    return false;
            }
            return true;
        }
}

bool Preadd(){
    if (it == tokenlist.end())
        return false;
    if (StrNumeric(*it))
        return true;
    if (!StrPlus(*it))
        return false;
    it++;
    if (!Preadd())
        return false;
    it++;
    if (!Preadd())
        return false;
    return true;
}

list<list<string> > recognizer(list<string> input){
    list<string> valid, invalid;
    list<list<string> > rlist;
    tokenlist = input;
    if (!StrPlus(tokenlist.front())){
        invalid = tokenlist;
        rlist.push_back(valid);
        rlist.push_back(invalid);
        return rlist;
    }
    it = tokenlist.begin();
    it++;
    if (!Preadd()){
        invalid = tokenlist;
        rlist.push_back(valid);
        rlist.push_back(invalid);
        return rlist;
    }
    it++;
    if (!Preadd()){
        invalid = tokenlist;
        rlist.push_back(valid);
        rlist.push_back(invalid);
        return rlist;
    }
    list<string>::iterator itt = it;
    itt++;
    for (; itt != tokenlist.end(); ++itt)
        invalid.push_back(*itt);
    valid.push_front(*it);
    while (it != tokenlist.begin()){
        it--;
        valid.push_front(*it);
    }
    rlist.push_back(valid);
    rlist.push_back(invalid);
    return rlist;
}

int main(int argc, char* argv[])
{
    ifstream myfile("file.txt");
    if (myfile.is_open()){
        string temp;
        list<list<string> > rlist;
        list<string> valid, invalid;
        while (getline(myfile, temp)){
            list<string> strList = stringtoken(temp);
            rlist = recognizer(strList);
            valid = rlist.front();
            invalid = rlist.back();
            cout << "valid:" << endl;
            for (string item : valid)
            {
                cout << item << ' ' << flush;
            }
            cout << endl<<"invald:"<<endl;
            for (string item : invalid)
            {
                cout << item << ' ' << flush;
            }
            cout << endl;
            
        }
    }
    else
        cout << "Can't find the file!" << endl;
    return 0;
}