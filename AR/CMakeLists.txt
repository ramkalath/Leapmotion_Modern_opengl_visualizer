cmake_minimum_required(VERSION 3.4)

set(project_name "AR")
# setting project name
project(${project_name})

# here add all the cpp files involved in the project
add_executable(${project_name} ./src/main.cpp) # (TODO: enter the cpp files after the project name one after the other with the path)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(EXECUTABLE_OUTPUT_PATH ../bin)

# add all the include files
target_include_directories(${project_name} PUBLIC ../include PUBLIC /usr/include PUBLIC /usr/local/include PUBLIC /usr/include/opencv4) # you can keep adding more if you want

#here add all the libraries that you included
target_link_libraries(${project_name} glfw3 GLEW GL GLU SOIL dl Xinerama Xrandr Xi Xcursor X11 Xxf86vm pthread assimp opencv_gapi  opencv_stitching  opencv_aruco  opencv_bgsegm  opencv_bioinspired  opencv_ccalib  opencv_cvv  opencv_dnn_objdetect  opencv_dnn_superres  opencv_dpm  opencv_highgui  opencv_face  opencv_freetype  opencv_fuzzy  opencv_hdf  opencv_hfs  opencv_img_hash  opencv_line_descriptor  opencv_quality  opencv_reg  opencv_rgbd  opencv_saliency  opencv_stereo  opencv_structured_light  opencv_phase_unwrapping  opencv_superres  opencv_optflow  opencv_surface_matching  opencv_tracking  opencv_datasets  opencv_text  opencv_dnn  opencv_plot  opencv_videostab  opencv_video  opencv_videoio  opencv_viz  opencv_xfeatures2d  opencv_shape  opencv_ml  opencv_ximgproc  opencv_xobjdetect  opencv_objdetect  opencv_calib3d  opencv_imgcodecs  opencv_features2d  opencv_flann  opencv_xphoto  opencv_photo  opencv_imgproc  opencv_core)
