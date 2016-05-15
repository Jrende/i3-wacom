#include <cstdio>
#include <i3ipc++/ipc.hpp>
#include <iostream>
#include <unordered_map>
#include "util.hpp"
#include <sstream>

std::unordered_map<int, std::string> num_to_output;
std::unordered_map<std::string, std::string> outputs = Util::get_monitors();
std::vector<int> wacom_devices = Util::get_wacom_devices();

void set_wacom_area(int num) {
  for(int device: wacom_devices) {
    std::stringstream ss;
    ss << "xsetwacom --set " << device << " MapToOutput " << num_to_output[num];
    int res = system(ss.str().c_str());
    if(res != 0) {
      std::cout << "Unable to change area!\n";
    }
  }
}

void update_workspace_outputs(const auto& conn) {
  for(const auto& ws: conn.get_workspaces()) {
    num_to_output[ws->num] = outputs[ws->output];
  }
}

int main(int argc, char** argv) {
  i3ipc::connection conn;
  conn.subscribe(i3ipc::ET_WORKSPACE);
  update_workspace_outputs(conn);

  conn.signal_workspace_event.connect([&](const i3ipc::workspace_event_t&  ev) {
    switch((char) ev.type) {
      case 'i':
        update_workspace_outputs(conn);
        break;
      case 'f':
        set_wacom_area(ev.current->num);
        break;
      default:
        break;
    }
  });
  
  conn.prepare_to_event_handling();

  while (true) {
    conn.handle_event();
  }
  return 0;
}
