#include "uart_to_mqtt.h"

#include <tbox/base/log.h>
#include <tbox/base/json.hpp>
#include <tbox/util/json.h>
#include <tbox/util/string.h>
#include <tbox/terminal/terminal_nodes.h>
#include <tbox/terminal/helper.h>

namespace hevake {

UartToMqtt::UartToMqtt(tbox::main::Context &ctx)
 : tbox::main::Module("uart_to_mqtt", ctx)
 , mqtt_(new Mqtt(ctx, *this))
 , uart_(new Uart(ctx, *this))
{
  add(mqtt_);
  add(uart_);
}

void UartToMqtt::onFillDefaultConfig(tbox::Json &js) {
  js["is_enable_log"] = false;
}

bool UartToMqtt::onInit(const tbox::Json &js) {
  tbox::util::json::GetField(js, "is_enable_log", is_enable_log_);
  initShell();
  return true;
}

bool UartToMqtt::onStart() {
  LogInfo("started");
  return true;
}

void UartToMqtt::onStop() {
  LogInfo("stoped");
}

void UartToMqtt::onMqttConnected() {
  LogInfo("mqtt connected");
  is_mqtt_online_ = true;
}

void UartToMqtt::onMqttDisconnected() {
  LogInfo("mqtt disconnected");
  is_mqtt_online_ = false;
}

void UartToMqtt::onMqttRecv(const void *data_ptr, size_t data_size) {
  if (is_enable_log_) {
    std::string hex_str = tbox::util::string::RawDataToHexStr(data_ptr, data_size);
    LogInfo("mqtt recv [%d]: %s", data_size, hex_str.c_str());
  }

  uart_->send(data_ptr, data_size);
}

void UartToMqtt::onUartRecv(const void *data_ptr, size_t data_size) {
  if (is_enable_log_) {
    std::string hex_str = tbox::util::string::RawDataToHexStr(data_ptr, data_size);
    LogInfo("uart recv [%d]: %s", data_size, hex_str.c_str());
  }

  if (is_mqtt_online_)
    mqtt_->send(data_ptr, data_size);
}

void UartToMqtt::initShell() {
  auto shell = ctx().terminal();
  auto dir_node = shell->createDirNode();

  shell->mountNode(shell->rootNode(), dir_node, "uart_to_mqtt");
  tbox::terminal::AddFuncNode(*shell, dir_node, "is_enable_log", is_enable_log_);
}

}
