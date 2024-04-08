#include <tbox/main/module.h>
#include "uart_to_mqtt.h"

namespace tbox {
namespace main {

void RegisterApps(Module &apps, Context &ctx) {
  apps.add(new hevake::UartToMqtt(ctx));
}

std::string GetAppDescribe() {
  return "This is a UART <--> MQTT middleware.";
}

void GetAppVersion(int &major, int &minor, int &rev, int &build) {
  major = 1;
  minor = 0;
  rev = 0;
  build = 0;
}

}
}
