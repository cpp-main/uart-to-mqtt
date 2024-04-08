#ifndef MQTT_H
#define MQTT_H

#include <tbox/main/module.h>
#include <tbox/mqtt/client.h>

namespace hevake {

/**
 * Mqtt模块
 */
class Mqtt : public tbox::main::Module {
 public:
  class Parent {
   public:
    virtual void onMqttConnected() = 0;
    virtual void onMqttDisconnected() = 0;
    virtual void onMqttRecv(const void *data_ptr, size_t data_size) = 0;
  };

  explicit Mqtt(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;
  virtual void onCleanup() override;

 public:
  void send(const void *data_ptr, size_t data_size);

 private:
  Parent &parent_;
  tbox::mqtt::Client mqtt_;
  std::string send_topic_;
};

}

#endif //MQTT_H
