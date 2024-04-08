#ifndef UART_TO_MQTT_H
#define UART_TO_MQTT_H

#include <tbox/main/module.h>
#include "mqtt.h"
#include "uart.h"

namespace hevake {

class UartToMqtt : public tbox::main::Module,
                   public Mqtt::Parent,
                   public Uart::Parent {
 public:
  explicit UartToMqtt(tbox::main::Context &ctx);

 protected:
  virtual void onFillDefaultConfig(tbox::Json &js) override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

  virtual void onMqttConnected() override;
  virtual void onMqttDisconnected() override;
  virtual void onMqttRecv(const void *data_ptr, size_t data_size) override;
  virtual void onUartRecv(const void *data_ptr, size_t data_size) override;

  void initShell();

 private:
  Mqtt *mqtt_; 
  Uart *uart_; 
  bool is_mqtt_online_ = false;
  bool is_enable_log_ = false;
};

}

#endif //UART_TO_MQTT_H
