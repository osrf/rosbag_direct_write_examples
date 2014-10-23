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

#include <iostream>

#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <sensor_msgs/Image.h>

int main(int argc, char ** argv)
{
  rosbag::Bag bag;
  std::string bag_name = "test.bag";
  if (argc > 1)
  {
    bag_name = argv[1];
  }
  bag.open(bag_name, rosbag::bagmode::Read);

  std::vector<std::string> topics;
  topics.push_back(std::string("camera"));

  rosbag::View view(bag, rosbag::TopicQuery(topics));

  for(auto m : view)
  {
    std::cout << "Topic: " << m.getTopic() << std::endl;
    auto msg = m.instantiate<sensor_msgs::Image>();
    if (msg != nullptr)
      std::cout << msg->header.stamp << std::endl;
  }

  bag.close();
}
