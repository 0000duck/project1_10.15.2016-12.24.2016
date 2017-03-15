/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fileMethods.h
 * Author: jcarlos2289
 *
 * Created on 9 de diciembre de 2016, 13:50
 */

#ifndef FILEMETHODS_H
#define FILEMETHODS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class fileMethods {
public:
    fileMethods();
    fileMethods(const fileMethods& orig);
    virtual ~fileMethods();
    static void saveData(std::string fileName, std::string text, bool append);
    static std::vector<std::string> openFile(std::string filePath);
    static void print(std::string s);
private:

};



#endif /* FILEMETHODS_H */

