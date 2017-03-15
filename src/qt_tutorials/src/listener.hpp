
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef LISTENER_NODE_HPP_
#define LISTENER_NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
//#define emit Q_EMIT
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include "../src/qnode.hpp"
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "caffe_msg_tagger/PredictionData.h"
#include "caffe_msg_tagger/PredictionGroup.h"
#include "svm_service_msg/svmService.h"
#endif


#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/String.h>
#include <string>

/*****************************************************************************
** Class
*****************************************************************************/

class Listener : public QNode {
protected:
  void run();
  void msleep(int ms);

public:
  Listener(int argc, char** argv);
  virtual ~Listener() {}
  //void run();
  void Videorun();
  void ros_comms_init();

private:

  cv::Mat frame;
  int frameRate;
  cv::Mat RGBframe;
  QImage img;
  void guiCallback(const caffe_msg_tagger::PredictionGroup msg);

  ros::Subscriber sub;
  // image_transport::Subscriber sub;

  std::string VidriloFind(std::string value);
};

#endif /* LISTENER_NODE_HPP_ */
