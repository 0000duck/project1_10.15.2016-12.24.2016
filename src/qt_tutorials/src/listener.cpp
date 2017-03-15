
/*****************************************************************************
** Includes
*****************************************************************************/

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <boost/lexical_cast.hpp>
#endif

#include <string>
#include <sstream>
#include "listener.hpp"

#include <std_msgs/String.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

/*****************************************************************************
** Implementation
*****************************************************************************/
std::map<std::string, std::string> mapOfWords;

Listener::Listener(int argc, char** argv ) :
  QNode(argc,argv,"qlistener")
{}

void Listener::ros_comms_init() {
  ros::NodeHandle n;
  sub = n.subscribe("/gui_caffe_ret",1,&Listener::guiCallback,this);
}

void Listener::guiCallback(const caffe_msg_tagger::PredictionGroup msg) {


  // Inserting data in std::map
  mapOfWords.insert(std::make_pair("1", "HallEntrance"));
  mapOfWords.insert(std::make_pair("2", "ProfessorRoom"));
  mapOfWords.insert(std::make_pair("3", "StudentsRoom"));
  mapOfWords.insert(std::make_pair("4", "TechnicalRoom"));
  mapOfWords.insert(std::make_pair("5", "Toilet"));
  mapOfWords.insert(std::make_pair("6", "Secretary"));
  mapOfWords.insert(std::make_pair("7", "Videoconference"));
  mapOfWords.insert(std::make_pair("8", "Warehouse"));
  mapOfWords.insert(std::make_pair("9", "ElevatorArea"));
  mapOfWords.insert(std::make_pair("10","Corridor"));


  //label
  for(int i=0;i<10;i++)
  {
    QNode::texto[i] = msg.predictions.label.at(i).c_str();
    QNode::textoUpdated();
  }
  //label svm
  for(int i=0;i<10;i++)
  {
    std::string txt = msg.svm_predictions.label.at(i).c_str();
   // std::cout<<"label: "<<txt<<std::endl;
    QNode::texto_svm[i] = Listener::VidriloFind(txt);
    QNode::textoUpdatedSVM();
  }

  //video
  cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg.image, "bgr8");
  cv::Mat image = cv_ptr->image;
  frame = image;
  if(!frame.empty())
  {
    Videorun();
  }
  //progress bar caffe
  for(int n=0;n<10;n++)
  {
    float porcentaje = msg.predictions.confidence.at(n);
    porcentaje = porcentaje*100;
    int porc = (int)porcentaje;
    QNode::valor[n]=porc;
    QNode::valueUpdate();

      std::cout<<"#: "<<n<< " : "<<valor[n]<<" "<<porc<<std::endl;
  }

  //progress bar svm
  for(int n=0;n<10;n++)
  {
    float porcentaje = msg.svm_predictions.confidence.at(n);
    std::cout<<"valor: "<<porcentaje<<std::endl;
    porcentaje = porcentaje*100;
    int porc = (int)porcentaje;
    QNode::valor_svm[n]=porc;
    QNode::valueUpdateSVM();
  }
}

void Listener::run() {
  ros::spin();
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void Listener::Videorun()
{
  if (frame.channels()== 3){
    cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
    img = QImage((const unsigned char*)(RGBframe.data),
                 RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
  }
  else
  {
    img = QImage((const unsigned char*)(frame.data),
                 frame.cols,frame.rows,QImage::Format_Indexed8);
  }
  QNode::processedImage(img);
}

/*map of VIDRILO*/


std::string Listener::VidriloFind(std::string value)
{
  std::string vidriloPlace="lol";

  // Iterate through all elements in std::map and search for the passed element
  std::map<std::string, std::string>::iterator it = mapOfWords.begin();
  while(it != mapOfWords.end())
  {

    if(value.compare(it->first)==0){
      vidriloPlace = it->second;
      return vidriloPlace;
      break;
    }
    it++;
  }
}

//if(value.compare("1")==0) {
//  vidriloPlace="HallEntrance";
//}else
//  if(value.compare("2")==0) {
//  vidriloPlace="ProfessorRoom";
//}else
//  if(value.compare("3")==0) {
//  vidriloPlace="StudentsRoom";
//}else
//  if(value.compare("4")==0) {
//  vidriloPlace="TechnicalRoom";
//}else
//  if(value.compare("5")==0) {
//  vidriloPlace="Toilet";
//}else
//  if(value.compare("6")==0) {
//  vidriloPlace="Secretary";
//}else
//  if(value.compare("7")==0) {
//  vidriloPlace="Videoconference";
//}else
//  if(value.compare("8")==0) {
//  vidriloPlace="Warehouse";
//}else
//  if(value.compare("9")==0) {
//  vidriloPlace="ElevatorArea";
//}else
//  if(value.compare("10")==0) {
//  vidriloPlace="Corridor";
//}
