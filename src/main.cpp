#include <cstdio>
#include <i3ipc++/ipc.hpp>
#include <iostream>
#include <unordered_map>
#include "util.hpp"
#include <sstream>

std::unordered_map<int, std::string> num_to_output;
std::unordered_map<std::string, std::string> outputs;

void set_wacom_area(int num) {
  for(int device: Util::get_wacom_devices()) {
    std::stringstream ss;
    ss << "xsetwacom --set " << device << " MapToOutput " << num_to_output[num];
    int res = system(ss.str().c_str());
    if(res != 0) {
      std::cerr << "Unable to remap wacom viewport!\n";
    }
  }
}

void update_workspace_outputs(const i3ipc::connection& connection) {
  for(const auto& ws: connection.get_workspaces()) {
    num_to_output[ws->num] = outputs[ws->output];
  }
}

int main(int argc, char** argv) {
  outputs = Util::get_monitors();
  i3ipc::connection connection;
  bool status = connection.subscribe(i3ipc::ET_WORKSPACE);
  if(!status) {
    std::cerr << "Unable to subscribe to i3 ET_WORKSPACE events!\n";
  }
  update_workspace_outputs(connection);
  set_wacom_area(1);

  connection.signal_workspace_event.connect([&](const i3ipc::workspace_event_t&  ev) {
    switch((char) ev.type) {
      case 'i':
        update_workspace_outputs(connection);
        break;
      case 'f':
        set_wacom_area(ev.current->num);
        break;
      default:
        break;
    }
  });

  connection.prepare_to_event_handling();
  while (true) {
    connection.handle_event();
  }
  return 0;
}
