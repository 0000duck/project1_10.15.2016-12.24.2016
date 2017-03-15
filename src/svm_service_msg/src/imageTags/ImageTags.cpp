/* 
 * File:   ImageTags.cpp
 * Author: jcarlos2289
 * 
 * Created on 23 de octubre de 2016, 15:56
 */

#include <set>

#include "ImageTags.h"

ImageTags::ImageTags(std::string in) {
     imageName = in;
    tags.clear();
    threshold = 0;
    // tags=new ConcurrentHashMap<String,Float>();
}

void ImageTags::init(std::string in) {
    imageName = in;
    tags.clear();
    threshold = 0;
    // tags=new ConcurrentHashMap<String,Float>();
}

void ImageTags::setThreshold(float th) {
    threshold = th;
}

void ImageTags::setCoords(double x, double y) {
    xcoord = x;
    ycoord = y;
}

void ImageTags::setCategory(std::string cat) {
    category = cat;
}

void ImageTags::setCategoryNumber(int cat) {
    classNumber = cat;
}

std::string& ImageTags::getCategory() {
    return this->category ;
}
int ImageTags::getClassNumber() {
    return this->classNumber ;
}



std::vector<std::string> ImageTags::split(std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void ImageTags::addTag(std::string line) {
    float value;
    std::vector<std::string> splitString = split(line, '-');
    std::string::size_type sz;
    // alias of size_t
    value = ::atof(splitString.at(1).c_str()); //std::stof(splitString.at(1), &sz);
    if (value >= threshold)
        tags.insert(std::pair<std::string, float>(splitString.at(0), value)); //tags.put(split[0], value);

}

std::set<std::string> ImageTags::getKeys() {

    //http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
    // std::vector<std::string> retval;
    std::set<std::string> keys;
    std::map<std::string, float>::const_iterator itr;
    for (itr = tags.begin(); itr != tags.end(); ++itr) {
        //retval.push_back( (*itr).first);
        keys.insert((*itr).first);
    }

    return keys;

}

std::vector<std::string> ImageTags::getKeysVector() {

    //http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
    std::vector<std::string> retval;
    //std::set<std::string> keys;
    std::map<std::string, float>::const_iterator itr;
    for (itr = tags.begin(); itr != tags.end(); ++itr) {
        retval.push_back((*itr).first);
        //keys.insert((*itr).first);
    }

    return retval;
    
}

bool ImageTags::exists(std::string s) {
    std::map<std::string, float>::iterator it;
    bool val;
    if ((it = tags.find(s)) != tags.end())
        val = true;
    else
        val = false;

    return (val);
}

float ImageTags::getValue(std::string s) {
    if (tags.at(s) == NULL)
        return 0.0f;
    else
        return tags.at(s);
}

ImageTags::ImageTags(const ImageTags& orig) {
}

ImageTags::~ImageTags() {
}

