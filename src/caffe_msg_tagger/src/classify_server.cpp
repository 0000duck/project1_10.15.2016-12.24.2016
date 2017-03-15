#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "Classifier.h"
#include "caffe_msg_tagger/tagService.h"
#include "caffe_msg_tagger/PredictionData.h"

Classifier *classifier;
std::string model_path;
std::string weights_path;
std::string mean_file;
std::string label_file;
std::string image_path;

//ros::Publisher gPublisher;

std::string publishRet(const std::vector<Prediction> &predictions);
caffe_msg_tagger::PredictionData castPredictions(const std::vector<Prediction> &predictions);

bool classify(caffe_msg_tagger::tagService::Request &req,
              caffe_msg_tagger::tagService::Response &res)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(req.image, "bgr8");
        //cv::imwrite("rgb.png", cv_ptr->image);
        cv_ptr->encoding = "bgr8";
        cv::Mat img = cv_ptr->image;
        std::vector<Prediction> predictions = classifier->Classify(img, req.n);

        res.predictions = castPredictions(predictions);
        res.maxTag = publishRet(predictions);
        //ROS_INFO("sending back response =) ");   caffe_msg_tagger/PredictionData predictions
    }
    catch (cv_bridge::Exception &e)
    {
        std::cout << e.what() << std::endl;
        ROS_ERROR("Could not tag the image. =(");
        res.maxTag = "<------------------>";
    }

    return true;
}

std::string publishRet(const std::vector<Prediction> &predictions)
{
    //std_msgs::String msg;
    std::stringstream ss;

    for (size_t i = 0; i < 1; ++i)
    {
        Prediction p = predictions[i];
        ss << "[" << p.second << " - " << p.first << "]";
    }
    //msg.data = ss.str();
    return (ss.str());
}

caffe_msg_tagger::PredictionData castPredictions(const std::vector<Prediction> &predictions)
{
    
    std::stringstream ss;
    std::vector<double> confidence;
    std::vector<std::string> labels;

    for (size_t i = 0; i < predictions.size(); ++i)
    {
        Prediction p = predictions[i];
        //std_msgs::String msg;
        confidence.push_back(p.second);
        //msg.data = p.first;
        labels.push_back(p.first);

        //ss << "[" << p.second << " - " << p.first << "]";
    }

    caffe_msg_tagger::PredictionData outPredec;
    outPredec.n = predictions.size();
    outPredec.confidence.swap(confidence);
    outPredec.label.swap(labels);

    //msg.data = ss.str();
    return (outPredec);
}




int main(int argc, char **argv)
{
    // Check arguments
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <model_id> [<args>]" << std::endl;
        return 1;
    }

    //setup classifier parameters
    std::string caffe_path = argv[1];
    model_path = caffe_path + "/models/bvlc_alexnet/deploy.prototxt"; 
    weights_path = caffe_path + "/models/bvlc_alexnet/bvlc_alexnet.caffemodel";
    mean_file = caffe_path + "/data/ilsvrc12/imagenet_mean.binaryproto";
    label_file = caffe_path + "/data/ilsvrc12/synset_words_cut.txt";

    if (!boost::filesystem::exists(model_path) ||
        !boost::filesystem::exists(weights_path) ||
        !boost::filesystem::exists(mean_file) ||
        !boost::filesystem::exists(label_file))
    {
        ROS_ERROR("Please, check that the following files exist");
        ROS_ERROR(" - %s", model_path.c_str());
        ROS_ERROR(" - %s", weights_path.c_str());
        ROS_ERROR(" - %s", mean_file.c_str());
        ROS_ERROR(" - %s", label_file.c_str());
       
        return 1;
    }

    ros::init(argc, argv, "classifier_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("tag_Service", classify);

    classifier = new Classifier(model_path, weights_path, mean_file, label_file);
    ROS_INFO("Ready to tag an image.");
    ros::spin();
    delete classifier;
    ros::shutdown();
    return 0;
}