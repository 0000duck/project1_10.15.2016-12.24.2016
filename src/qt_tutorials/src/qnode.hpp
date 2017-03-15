/**
 * @file /eros_qtalker/include/eros_qtalker/qnode.hpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef NODE_HPP_
#define NODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
//#undef emit
/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
  Q_OBJECT

public:
  QNode(int argc, char** argv, const std::string &name );
  virtual ~QNode();

  bool on_init();
  bool on_init(const std::string &master_url, const std::string &host_url);
  void shutdown();
  virtual void run() = 0;

  // QStringListModel* loggingModel() { return &logging; }
  const std::string& nodeName() { return node_name; }
  const std::string& loggingTexto(int ntext) {return texto[ntext];}
  const int& loggingValue(int nvalue){return valor[nvalue];}
  //SVM consts
  const std::string& loggingTextoSVM(int svm_ntext) {return texto_svm[svm_ntext];}
  const int& loggingValueSVM(int svm_nvalue){return valor_svm[svm_nvalue];}
Q_SIGNALS:
  // void loggingUpdated();
  void rosShutdown();
  //Signal to output frame to be displayed
  void processedImage(const QImage &image);
  //Signal to output text of CAFFE
  void textoUpdated();
  //Signal to CAFFE progress bar
  void valueUpdate();
  //Signal to output text of SVM
  void textoUpdatedSVM();
  //Signal to SVM progress bar
  void valueUpdateSVM();
protected:
  virtual void ros_comms_init() = 0;
  int init_argc;
  char** init_argv;
  // QStringListModel logging;
  std::string texto[10]; //text to CAFFE label
  std::string texto_svm[10]; //text to svm label
  std::string node_name;
  int valor[10]; // value to progress bar
  int valor_svm[10]; // value to svm progress bar
};

#endif /* NODE_HPP_ */
