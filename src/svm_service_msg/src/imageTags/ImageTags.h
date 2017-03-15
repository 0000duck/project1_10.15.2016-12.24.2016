/* 
 * File:   ImageTags.h
 * Author: jcarlos2289
 *
 * Created on 23 de octubre de 2016, 15:56
 */

#ifndef IMAGETAGS_H
#define	IMAGETAGS_H

#include <string> 
#include <map>
#include <vector>
#include <iostream>  
#include <stdlib.h> 
#include <sstream>
#include <set>

class ImageTags {
public:
    

    std::string imageName;
    std::map<std::string, float> tags;
    double xcoord, ycoord;
    float threshold;
    std::string category;
    int classNumber;

    
    ImageTags(std::string in);
    ImageTags(const ImageTags& orig);
    virtual ~ImageTags();
    void init(std::string in);
    std::vector<std::string> split(std::string s, char delim);
    void addTag(std::string line);
    void setCategory(std::string cat);
    void setCoords(double x, double y);
    void setThreshold(float th);
    std::set<std::string> getKeys ();
    std::vector<std::string> getKeysVector();
    bool exists (std::string s);
    float getValue (std::string s);
    std::string& getCategory();
    void setCategoryNumber(int cat);
    int getClassNumber();
    
    
     
    
    
private:

};

#endif	/* IMAGETAGS_H */

