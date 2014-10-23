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

#include <ros/ros.h>
#include <rosbag/bag_direct.h>

#include <sensor_msgs/Image.h>

#include "common.h"

/** Specialized Functions to take advantage of direct memory writing **/

template<> bool
rosbag::has_direct_data<sensor_msgs::Image>()
{
  return true;
}

template<> void
rosbag::serialize_to_buffer(VectorBuffer &buffer, const sensor_msgs::Image &msg)
{
  size_t buffer_length = ros::serialization::serializationLength(msg);
  // Minus size of image data
  buffer_length -= msg.data.size();
  // Minus size of size of image data
  buffer_length -= 4;
  // Save currect buffer position and resize
  size_t start_offset = buffer.size();
  buffer.resize(buffer.size() + buffer_length);
  // Create a OStream
  ros::serialization::OStream s(buffer.data() + start_offset, buffer_length);
  // Write out everything but image data
  ros::serialization::serialize(s, msg.header);
  ros::serialization::serialize(s, msg.height);
  ros::serialization::serialize(s, msg.width);
  ros::serialization::serialize(s, msg.encoding);
  ros::serialization::serialize(s, msg.is_bigendian);
  ros::serialization::serialize(s, msg.step);
  // Write the size of the data which comes next in serialize_to_file
  write_to_buffer(buffer, msg.data.size(), 4);
}

template<> void
rosbag::serialize_to_file(DirectFile &file, const sensor_msgs::Image &msg)
{
  assert((file.get_offset() % 4096) == 0);
  // Write the data directly to the file from the memory
  file.write_data(msg.data.data(), msg.data.size());
}

/* Example main */

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "direct_bagger");
  auto n = ros::NodeHandle();
  rosbag::DirectBag bag("test_direct.bag");

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
