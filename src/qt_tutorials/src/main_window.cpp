/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "main_window.hpp"

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(QNode *node, QWidget *parent) :
  QMainWindow(parent),
  qnode(node)
{
  ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
  QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application

  ReadSettings();
  setWindowIcon(QIcon(":/images/icon.png"));
  ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).

  setWindowTitle(QApplication::translate("MainWindowDesign", qnode->nodeName().c_str(), 0));

  /*********************
    ** Logging
    **********************/
  // ui.view_logging->setModel(qnode->loggingModel());

  // QObject::connect(qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));
  // QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

  //video
  QObject::connect(qnode, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));

  //labels
  ui.etiqueta->setText("");
  ui.etiqueta_2->setText("");
  ui.etiqueta_3->setText("");
  ui.etiqueta_4->setText("");
  ui.etiqueta_5->setText("");
  ui.etiqueta_6->setText("");
  ui.etiqueta_7->setText("");
  ui.etiqueta_8->setText("");
  ui.etiqueta_9->setText("");
  ui.etiqueta_10->setText("");
  QObject::connect(qnode, SIGNAL(textoUpdated()), this, SLOT(setTextLabel()));

  //labels SVM
  ui.svm_lbl_1->setText("");
  ui.svm_lbl_2->setText("");
  ui.svm_lbl_3->setText("");
  ui.svm_lbl_4->setText("");
  ui.svm_lbl_5->setText("");
  ui.svm_lbl_6->setText("");
  ui.svm_lbl_7->setText("");
  ui.svm_lbl_8->setText("");
  ui.svm_lbl_9->setText("");
  ui.svm_lbl_10->setText("");
  QObject::connect(qnode, SIGNAL(textoUpdatedSVM()), this, SLOT(setTextLabelSVM()));

  //progress bar caffe

  this->ui.progressBar->setValue(0);
  this->ui.progressBar_2->setValue(0);
  this->ui.progressBar_3->setValue(0);
  this->ui.progressBar_4->setValue(0);
  this->ui.progressBar_5->setValue(0);
  this->ui.progressBar_6->setValue(0);
  this->ui.progressBar_7->setValue(0);
  this->ui.progressBar_8->setValue(0);
  this->ui.progressBar_9->setValue(0);
  this->ui.progressBar_10->setValue(0);

  connect(qnode, SIGNAL(valueUpdate()), this, SLOT(updateProgressBar()));


  //progress bar svm

  this->ui.svm_progressBar_1->setValue(0);
  this->ui.svm_progressBar_2->setValue(0);
  this->ui.svm_progressBar_3->setValue(0);
  this->ui.svm_progressBar_4->setValue(0);
  this->ui.svm_progressBar_5->setValue(0);
  this->ui.svm_progressBar_6->setValue(0);
  this->ui.svm_progressBar_7->setValue(0);
  this->ui.svm_progressBar_8->setValue(0);
  this->ui.svm_progressBar_9->setValue(0);
  this->ui.svm_progressBar_10->setValue(0);
  connect(qnode, SIGNAL(valueUpdateSVM()), this, SLOT(updateProgressBarSVM()));

  QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
  /***********************
    ** Auto Start
    **********************/
  if ( ui.checkbox_remember_settings->isChecked() ) {
    on_button_connect_clicked(true);
  }
}

/*progress bars*/
//Progress bar caffe
void MainWindow::updateProgressBar()
{
  this->ui.progressBar->setValue(qnode->loggingValue(0));
  this->ui.progressBar_2->setValue(qnode->loggingValue(1));
  this->ui.progressBar_3->setValue(qnode->loggingValue(2));
  this->ui.progressBar_4->setValue(qnode->loggingValue(3));
  this->ui.progressBar_5->setValue(qnode->loggingValue(4));
   this->ui.progressBar_6->setValue(qnode->loggingValue(5));
   this->ui.progressBar_7->setValue(qnode->loggingValue(6));
   this->ui.progressBar_8->setValue(qnode->loggingValue(7));
   this->ui.progressBar_9->setValue(qnode->loggingValue(8));
   this->ui.progressBar_10->setValue(qnode->loggingValue(9));
}

//Progress bar svm
void MainWindow::updateProgressBarSVM()
{
  this->ui.svm_progressBar_1->setValue(qnode->loggingValueSVM(0));
  this->ui.svm_progressBar_2->setValue(qnode->loggingValueSVM(1));
  this->ui.svm_progressBar_3->setValue(qnode->loggingValueSVM(2));
  this->ui.svm_progressBar_4->setValue(qnode->loggingValueSVM(3));
  this->ui.svm_progressBar_5->setValue(qnode->loggingValueSVM(4));
  this->ui.svm_progressBar_6->setValue(qnode->loggingValueSVM(5));
  this->ui.svm_progressBar_7->setValue(qnode->loggingValueSVM(6));
  this->ui.svm_progressBar_8->setValue(qnode->loggingValueSVM(7));
  this->ui.svm_progressBar_9->setValue(qnode->loggingValueSVM(8));
  this->ui.svm_progressBar_10->setValue(qnode->loggingValueSVM(9));
}

/*labels*/
//caffe labels
void MainWindow::setTextLabel(){
  ui.etiqueta->setText(qnode->loggingTexto(0).c_str());
  ui.etiqueta_2->setText(qnode->loggingTexto(1).c_str());
  ui.etiqueta_3->setText(qnode->loggingTexto(2).c_str());
  ui.etiqueta_4->setText(qnode->loggingTexto(3).c_str());
  ui.etiqueta_5->setText(qnode->loggingTexto(4).c_str());
  ui.etiqueta_6->setText(qnode->loggingTexto(5).c_str());
  ui.etiqueta_7->setText(qnode->loggingTexto(6).c_str());
  ui.etiqueta_8->setText(qnode->loggingTexto(7).c_str());
  ui.etiqueta_9->setText(qnode->loggingTexto(8).c_str());
  ui.etiqueta_10->setText(qnode->loggingTexto(9).c_str());
}
//svm labels
void MainWindow::setTextLabelSVM(){
  ui.svm_lbl_1->setText(qnode->loggingTextoSVM(0).c_str());
  ui.svm_lbl_2->setText(qnode->loggingTextoSVM(1).c_str());
  ui.svm_lbl_3->setText(qnode->loggingTextoSVM(2).c_str());
  ui.svm_lbl_4->setText(qnode->loggingTextoSVM(3).c_str());
  ui.svm_lbl_5->setText(qnode->loggingTextoSVM(4).c_str());
  ui.svm_lbl_6->setText(qnode->loggingTextoSVM(5).c_str());
  ui.svm_lbl_7->setText(qnode->loggingTextoSVM(6).c_str());
  ui.svm_lbl_8->setText(qnode->loggingTextoSVM(7).c_str());
  ui.svm_lbl_9->setText(qnode->loggingTextoSVM(8).c_str());
  ui.svm_lbl_10->setText(qnode->loggingTextoSVM(9).c_str());
}

void MainWindow::updatePlayerUI(QImage img)
{
  if (!img.isNull())
  {
    ui.CVviewer->setAlignment(Qt::AlignCenter);
    ui.CVviewer->setPixmap(QPixmap::fromImage(img).scaled(ui.CVviewer->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
  }
}
MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
  QMessageBox msgBox;
  msgBox.setText("Couldn't find the ros master.");
  msgBox.exec();
  close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check ) {
  if ( ui.checkbox_use_environment->isChecked() ) {
    if ( !qnode->on_init() ) {
      showNoMasterMessage();
    } else {
      ui.button_connect->setEnabled(false);
    }
  } else {
    if ( ! qnode->on_init(
           ui.line_edit_master->text().toStdString(),
           ui.line_edit_host->text().toStdString() )
         ) {
      showNoMasterMessage();
    } else {
      ui.button_connect->setEnabled(false);
      ui.line_edit_master->setReadOnly(true);
      ui.line_edit_host->setReadOnly(true);
    }
  }
}

void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
  bool enabled;
  if ( state == 0 ) {
    enabled = true;
  } else {
    enabled = false;
  }
  ui.line_edit_master->setEnabled(enabled);
  ui.line_edit_host->setEnabled(enabled);
}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::about(this, tr("About"),tr("<h2>Caffe Msg Tagger QT Listener</h2><p>Rovit</p><p>This package is a graphic subscriber of package Caffe Msg Tagger, created by Jose Carlos Rangel. In this package you can see 5 tags and their respective confidence level shown in percentaje.Also you could see the video analyzed in real time.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
  QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("windowState").toByteArray());
  QString master_url = settings.value("master_url",QString("http://127.0.0.1:11311/")).toString();
  QString host_url = settings.value("host_url", QString("127.0.0.1")).toString();
  QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
  ui.line_edit_master->setText(master_url);
  ui.line_edit_host->setText(host_url);
  bool remember = settings.value("remember_settings", false).toBool();
  ui.checkbox_remember_settings->setChecked(remember);
  bool checked = settings.value("use_environment_variables", false).toBool();
  ui.checkbox_use_environment->setChecked(checked);
  if ( checked ) {
    ui.line_edit_master->setEnabled(false);
    ui.line_edit_host->setEnabled(false);
  }
}

void MainWindow::WriteSettings() {
  QSettings settings("Qt-Ros Package", qnode->nodeName().c_str());
  settings.setValue("geometry", geometry());
  settings.setValue("master_url",ui.line_edit_master->text());
  settings.setValue("host_url",ui.line_edit_host->text());
  settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
  settings.setValue("windowState", saveState());
  settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  qnode->shutdown();
  WriteSettings();
  QMainWindow::closeEvent(event);
}
