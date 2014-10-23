/* Copyright 2014 Open Source Robotics Foundation, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>

#include <ros/ros.h>
#include <rosbag/bag.h>

#include <sensor_msgs/Image.h>

#include "common.h"


int main(int argc, char *argv[])
{
  ros::init(argc, argv, "bagger");
  auto n = ros::NodeHandle();
  rosbag::Bag bag;
  bag.open("test.bag", rosbag::bagmode::Write);

  size_t number_of_iterations = get_number_of_iterations(argc, argv);

  size_t width = 1024, height = 768;
  sensor_msgs::Image image;
  image.header.stamp = ros::Time::now();
  image.header.frame_id = "/camera";
  image.height = width;
  image.width = height;
  image.encoding = "Encoding 1";
  image.is_bigendian = true;
  image.step = 1;
  image.data = std::vector<uint8_t>(width * height, 0x12);
  for (size_t i = 0; i < number_of_iterations; ++i)
  {
    image.header.stamp = ros::Time::now();

    bag.write("camera", image.header.stamp, image);
  }

  bag.close();
}