#Message for sending the prediction data to the gui

caffe_msg_tagger/PredictionData predictions  # Labels and Confidence Values
sensor_msgs/Image image                      # Original Image
caffe_msg_tagger/PredictionData svm_predictions  # Labels and Confidence Values of svm
