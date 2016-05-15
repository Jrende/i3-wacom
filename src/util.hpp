#pragma once
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Util {
  namespace {
    std::string exec(const char* cmd) {
      char buffer[128];
      std::string result = "";
      std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
      if (!pipe) throw std::runtime_error("popen() failed!");
      while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
          result += buffer;
      }
      return result;
    }
  }

  std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }

  std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }

  std::vector<int> get_wacom_devices() {
    std::string xsetwacom_output = exec("xsetwacom --list devices");
    std::vector<std::string> lines = split(xsetwacom_output, '\t');
    std::vector<int> ids;
    for(const auto& line: lines) {
      if(line.find("id") != std::string::npos) {
        std::vector<std::string> tokens = split(line, ' ');
        auto num = tokens[1];
        ids.push_back(atoi(tokens[1].c_str()));
      }
    }
    return ids;
  }

  std::unordered_map<std::string, std::string> get_monitors() {
    std::string xrandr_output = exec("xrandr");
    std::vector<std::string> lines = split(xrandr_output, '\n');
    std::unordered_map<std::string, std::string> output;
    for(const auto& line: lines) {
      if(line.find(" connected ") != std::string::npos) {
        std::vector<std::string> tokens = split(line, ' ');
        output[tokens[0]] = tokens[2];
      }
    }
    return output;
  }
}
