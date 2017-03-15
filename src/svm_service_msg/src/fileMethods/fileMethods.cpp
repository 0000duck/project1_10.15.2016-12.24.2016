/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fileMethods.cpp
 * Author: jcarlos2289
 * 
 * Created on 9 de diciembre de 2016, 13:50
 */

#include "fileMethods.h"

fileMethods::fileMethods() {
}

fileMethods::fileMethods(const fileMethods& orig) {
}

fileMethods::~fileMethods() {
}

void fileMethods::saveData(std::string fileName, std::string text, bool append) {

    std::string svPath = fileName+".txt";
    
    if (append) {
        std::ofstream outputFile(svPath.c_str(), std::ofstream::out |std::ofstream::app);
        outputFile << text << std::endl;
        outputFile.close();

    } else {
        std::ofstream outputFile(svPath.c_str(), std::ofstream::out);
        outputFile << text << std::endl;
        outputFile.close();
    }



    std::cout << "File: " << svPath << " saved." << std::endl;
}

std::vector<std::string> fileMethods::openFile(std::string filePath){
    std::vector<std::string> outputList;
    
    std::ifstream fileData(filePath.c_str());
    std::string line;
    
    if (fileData.is_open())
    {
         while (getline(fileData, line)){
             outputList.push_back(line);
         }
         fileData.close();
    }else
    {
        outputList.push_back("Empty_file");
        return outputList;
    }
    
    
    return outputList;
    
}