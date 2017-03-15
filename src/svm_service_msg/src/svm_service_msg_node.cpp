#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include "caffe_msg_tagger/PredictionData.h"
#include "svm_service_msg/svmService.h"
#include "svm/svm.h"
#include "imageTags/ImageTags.h"
#include "fileMethods/fileMethods.h"

/*form main of svm project*/

#include <cstdlib>
#include <iostream>
//#include <bits/basic_string.h>
#include <fstream>
//#include <bits/stl_vector.h>
#include <vector>

#include <map>
#include <iosfwd>
//#include <bits/stringfwd.h>
//#include <bits/stl_map.h>
#include <iterator>
//#include <bits/stl_vector.h>
//#include <bits/stl_map.h>
#include <string>
#include <boost/lexical_cast.hpp>
//#include <bits/stl_vector.h>
//#include "ImageTags.h"
//#include "svm/svm.h"
//#include "svm/svm.cpp"

using namespace std;

struct svm_model *model;
std::vector<std::string> keyList;

double FindMax(int nclases, double *probResults);

std::vector<std::string> split(std::string s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

bool classify(svm_service_msg::svmService::Request &req,
              svm_service_msg::svmService::Response &res)
{

  /*test of svm project*/

  //test

  // std::ifstream descriptorTest("/home/ed/Documents/VidriloTags/Sequence2/Vidrilo_Sequence2_PlacesAlexNet/sequence2visual2.txt");

  //  std::string tagLineTest;

  //std::vector<int> svm_labels;
  std::vector<std::string> lbls;
  std::vector<double> confid;

  lbls = req.descriptor.label;
  confid = req.descriptor.confidence;

  ImageTags testImage("");
  for(int i=0;i<req.descriptor.n;i++){
    std::stringstream descriptorTest;
    descriptorTest <<lbls.at(i) <<"-"<<confid.at(i);
    testImage.addTag(descriptorTest.str());

  }

  svm_node *test_node = new svm_node[keyList.size() + 1];


  int j = 0;

  for (std::vector<std::string>::iterator it2 = keyList.begin(); it2 != keyList.end(); ++it2) {

    test_node[j].index = j + 1;
    test_node[j].value = testImage.tags.at((*it2));
    //std::cout<<j<<"-"<<test_node[j].index<<"-"<<test_node[j].value<<std::endl;
    ++j;
  }

  test_node[keyList.size()].index = -1;

  int nclases = svm_get_nr_class(model);
  double *probResults = new double[nclases];
  int *labels = new int[nclases];
  double predict_Normal;
  double predict_Prob = 0;
  int probModel = svm_check_probability_model(model);
  double max = 0;

  if (probModel > 0) {
    std::cout << "\npredictProb(before): " << predict_Prob << std::endl;
    predict_Prob = svm_predict_probability(model, test_node, probResults);
    svm_get_labels(model,labels);
  //  predict_Normal = svm_predict(model, test_node);
    std::cout << "predictPro(afer): " << predict_Prob << std::endl;
    std::stringstream ff;
    std::vector<std::string> lbl_prob;
    std::vector<double> proba;

    //ff << "\n\nPredict Normal " << predict_Normal << "\n";
    ff << "Predict Prob " << predict_Prob << "\n";
  //  ff << "Probs" << "\n\n";

    for (int i = 0; i < nclases; ++i) {
      ff << "label: "<<labels[i]<<" prob: "<<probResults[i] << "\n";
      lbl_prob.push_back(boost::lexical_cast<std::string>(labels[i]));
      proba.push_back(probResults[i]);

      max = FindMax(nclases, probResults);
    }

    std::cout << ff.str() << std::endl;
    std::cout << "\n max = " << max << std::endl;

    res.predictions.confidence = proba;
    res.predictions.label = lbl_prob;
    res.predictions.n = nclases;
  } else {
    std::cout << "\nNo se cuenta con informacion suficiente de probabilidad." << std::endl;
  }

  /*end code from svm project*/

  return true;


}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "svm_service_msg_node");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("svm_Service", classify);

  model = svm_load_model("/home/ed/vidriloClasificador/SVMTrain_Vidrilo/Vidrilo_ImageNetAlexNet.txt");
  keyList = fileMethods::openFile("/home/ed/vidriloClasificador/SVMTrain_Vidrilo/keyList_Vidrilo_ImageNetAlexNet_SQ1.txt");

  /*end svm code*/
  ROS_INFO("Ready to tag an image.");
  ros::spin();
  ros::shutdown();
  return 0;
}

/*svm function*/

double FindMax(int nclases, double *probResults) {
  double max;

  for (int i = 0; i < nclases; ++i) {
    if (max == 0) {
      max = probResults[i];
    } else if (max < probResults[i]) {
      max = probResults[i];
    }
  }
  return max;
}
