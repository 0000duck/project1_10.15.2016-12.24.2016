# Caffe Live Tagger 

Este repositorio contiene un paquete de ROS que permite la utilización de una camara para realizar una clasificación en tiempo real de los objetos en el campo de vista de la misma. Utilizando como clasificador un modelo pre-entrenado con [Caffe](http://caffe.berkeleyvision.org/), basados en CNN.

## Características 

* C++
* Openni (Kinect)
* Openni2 (Asus Xtion)
* ROS usb_cam
* Caffe

Este paquete se desarrollo en Ubuntu 14.04 con ROS Jade utilizando la version de Caffe disponible en su página de [git hub](https://github.com/BVLC/caffe/). La integración de Caffe con ROS (ros_caffe) utilizada es la que se encuentra [ros_caffe](https://github.com/tzutalin/ros_caffe). 


## Requerimientos

* [ROS](http://www.ros.org/)
* [Caffe](https://github.com/BVLC/caffe/)
* Modelos pre-entrenados de Caffe, (carpeta model y data de Caffe)


## Instalación

* Caffe
Para la configuración de Caffe se recomienda seguir las instrucciones disponibles en su [página](http://caffe.berkeleyvision.org/installation.html), utilizando la compilacion con *Make*, para generar los distribute de la libreria.

* Clonar el repositorio 
```
$ cd [CATKIN_WS]/src 
$ git clone `
```
* Editar la ubicacion de los distribute de Caffe en el CMakeList del paquete. Para ello editar las lineas:

```
set(CAFFE_INCLUDEDIR /home/my_libraries/caffe/build/include /home/my_libraries/caffe/distribute/include)
set(CAFFE_LINK_LIBRARAY /home/my_libraries/caffe/build/lib)
```
indicando la ubicación de la libreria en nuestro ordenador.

* Modelos
Esta aplicación utiliza el modelo pre-entrenado de ImageNet con AlexNet (BLVC AlexNet), disponible en el repositorio de Caffe como uno de sus ejemplos. Pero se puede emplear con cualquier modelo pre-entrenado con Caffe, al igual que con los demas ejemplos. Instrucciones de descarga disponibles en [Model_Zoo](http://caffe.berkeleyvision.org/model_zoo.html).
Para descargar el modelo de AlexNet Imagenet se ejecuta el comando "scripts/download_model_binary.py models/bvlc_alexnet", desde la ubucacion de Caffe en el ordenador. Este script se encuetra disponible dentro de la carpeta scripts de Caffe.
```
cd [CAFFE_DIR]
scripts/download_model_binary.py models/bvlc_alexnet

```
* Siguiendo lo pasos anteriores despues de la descarga los archivos necesarios para los modelos se encontraran en las siguientes ubicaciones en el ordenandor, donde *my_libraries* hace referencia a la ruta donde se ha instalado Caffe.
```
model : /home/my_libraries/caffe/models/bvlc_alexnet/deploy.prototxt
weights : /home/my_libraries/caffe/models/bvlc_alexnet/bvlc_alexnet.caffemodel
mean file:  /home/my_libraries/caffe/data/ilsvrc12/imagenet_mean.binaryproto
label file: /home/my_libraries/caffe/data/ilsvrc12/synset_words_cut.txt
```

Este repositorio incluye el fichero synset_words_cut.txt, el cual contiene un nombre reducido para cada una de los 1000 objetos que detecta el modelo. Para utilizarlo vasta con copiar y pegar el mismo en la carpeta de data/ilsvrc12/ en el directorio de Caffe. Si se desea utilizar el archivo de synset original del modelo se deberia modificar el fichero *caffe/live/tagger/src/classifier_server.cpp* y cambiar el nobre del synset por el nombre de la version original del fichero.

## Compilación

Una vez realizado los pasos anteriores, se procede a la compilacióon del paquete.
```
$ cd [CATKIN_WS]/ 
$ catkin_make install
```

## Ejecución

La ejecución se puede realizar empleando una camara web, Asus XTion o Microsoft Kinect 1.0.
Es necesario tambien editar los archivos de launch para especificar el lugar donde se encuentra Caffe en el ordenador. Para cada archivo la línea a editar es la siguiente.


```
 <arg name="caffe_path" default="/home/my_libraries/caffe" />  
```


En un nuevo terminal:

```
$ source [CATKIN_WS]/devel/setup.bash 
$ roslaunch caffe_live_tagger tagger.xtion.launch 
```

* Para utilizar Kinect: tagger.kinect.launch
* Para utilizar Camara Web: tagger.usb_cam.launch

Las predicciones apareceran en la misma terminal.

## Issues conocidos

* cublas: si al momento de compilar con "catkin_make" envia un error por la falta de cublas, se debe instalar el cuda toolkit para resolverlo, mediante la instrucción "sudo apt-get install nvidia-toolkit". Este problema se ha detectado en Ubuntu 14.04 y 16.04 con versiones de ROS Jade y Kinetic respectivamente.

* usb_cam: Hasta la ultima actualización no se encontraba disponible el paquete usb_cam para ROS Kinectic Kame.  




