# Caffe predictions for a single image

std_msgs/Header header
int32 n                  # Number of predictions
float64[] confidence    # Confidence value for the n predictions
string[] label          # Caffe labels for the n predictions
