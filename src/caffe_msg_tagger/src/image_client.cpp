/*
 * image_sender.cpp
 *
 *  Created on: octubre 7, 2016
 *      Author: jcarlos2289
 */

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <highgui.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "caffe_msg_tagger/tagService.h"
#include "caffe_msg_tagger/PredictionData.h"
#include "caffe_msg_tagger/PredictionGroup.h"
#include "svm_service_msg/svmService.h"

#include <vector>


//topic containing the image 
const std::string RECEIVE_IMG_TOPIC_NAME = "camera/rgb/image_raw";   
const std::string PUBLISH_RET_TOPIC_NAME = "/caffe_ret";
const std::string PUBLISH_GUI_TOPIC_NAME = "/gui_caffe_ret";


std::string model_path;
std::string weights_path;
std::string mean_file;
std::string label_file;
std::string image_path;

ros::Publisher gPublisher;
ros::Publisher guiPublisher;
ros::ServiceClient client;
ros::ServiceClient svm_client;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {

  try {
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    cv::Mat image = cv_ptr->image;
    cv::Mat cut;

    if (image.empty()) {
      std::cout << "Could not open or find the image" << std::endl;
      //return -1;
    }

    caffe_msg_tagger::PredictionGroup pGroup;
    caffe_msg_tagger::tagService srv;
    svm_service_msg::svmService svm_srv;

    srv.request.image = *msg;
    srv.request.n = 1000;

    if (client.call(srv))
    {
      std ::cout << "Sending data to gui." << std::endl;
      pGroup.image =*msg;
      pGroup.predictions = srv.response.predictions;
      //std ::cout << srv.response.tag << std::endl;

      /* SVM SERVICE CALL */

      svm_srv.request.descriptor = srv.response.predictions;
      if (svm_client.call(svm_srv))
      {
           ROS_ERROR("svm call");
        pGroup.svm_predictions = svm_srv.response.predictions;
      }
      else
      {
        ROS_ERROR("Failed to call service svm_Service");
        //return 1;
      }

      /*GPUBLISHER*/
      std_msgs::String msg;
      msg.data = srv.response.maxTag;
      gPublisher.publish(msg);
      guiPublisher.publish(pGroup);

    }
    else
    {
      ROS_ERROR("Failed to call service tag_Service");
      //return 1;
    }


  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

using namespace std;
using namespace cv;

int main(int argc, char **argv) {

  ros::init(argc, argv, "image_sender");

  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  // To receive an image from the topic, PUBLISH_RET_TOPIC_NAME
  image_transport::Subscriber sub = it.subscribe(RECEIVE_IMG_TOPIC_NAME, 1, imageCallback);
  gPublisher = nh.advertise<std_msgs::String>(PUBLISH_RET_TOPIC_NAME, 100);
  guiPublisher = nh.advertise<caffe_msg_tagger::PredictionGroup>(PUBLISH_GUI_TOPIC_NAME, 1);

  //define the service client
  client = nh.serviceClient<caffe_msg_tagger::tagService>("tag_Service");
  svm_client = nh.serviceClient<svm_service_msg::svmService>("svm_Service");
  ros::spin();

  ros::shutdown();
  return 0;
}
