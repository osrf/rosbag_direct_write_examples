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

#include <exception>
#include <iostream>
#include <string>

size_t get_number_of_iterations(int argc, char **argv)
{
  if (argc > 1)
  {
    auto on_error = [&](std::exception &e)
    {
      std::cerr << "Could not parse argument as unsigned integer: '"
                << argv[1] << "'" << std::endl;
    };
    try
    {
      return std::stoul(argv[1]);
    }
    catch(std::invalid_argument &e)
    {
      on_error(e);
      return 1;
    }
    catch(std::out_of_range &e)
    {
      on_error(e);
      return 1;
    }
  }
  return 100;
}
