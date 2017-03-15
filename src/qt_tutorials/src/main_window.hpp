
#ifndef QTUTORIALS_MAIN_WINDOW_H
#define QTUTORIALS_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#ifndef Q_MOC_RUN
#include "/home/ed/catkin_ws/build/qt_tutorials/ui_main_window.h"
#include "qnode.hpp"
#endif

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QNode *node, QWidget *parent = 0);
  ~MainWindow();

  void ReadSettings(); // Load up qt program settings at startup
  void WriteSettings(); // Save qt program settings when closing

  void closeEvent(QCloseEvent *event); // Overloaded function
  void showNoMasterMessage();

public Q_SLOTS:
  void on_actionAbout_triggered();
  void on_button_connect_clicked(bool check );
  void on_checkbox_use_environment_stateChanged(int state);
  //slot to video
  void updatePlayerUI(QImage img);
  //slot progress bar caffe
  void updateProgressBar();
  //slot progress bar svm
  void updateProgressBarSVM();
  //slot label Caffe
  void setTextLabel();
  //slot label SVM
  void setTextLabelSVM();
private:
  Ui::MainWindowDesign ui;
  QNode *qnode;
};

#endif // QTUTORIALS_MAIN_WINDOW_H
