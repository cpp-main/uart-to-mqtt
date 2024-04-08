#ifndef UART_H
#define UART_H

#include <tbox/main/module.h>
#include <tbox/network/uart.h>

namespace hevake {

/**
 * 串口通信模块
 */
class Uart : public tbox::main::Module {
 public:
  class Parent {
   public:
    virtual void onUartRecv(const void *data_ptr, size_t data_size) = 0;
  };

  explicit Uart(tbox::main::Context &ctx, Parent &parent);

 public:
  virtual void onFillDefaultConfig(tbox::Json &js) override;
  virtual bool onInit(const tbox::Json &js) override;
  virtual bool onStart() override;
  virtual void onStop() override;

 public:
  void send(const void *data_ptr, size_t data_size);

 protected:
  void onUartRecv(tbox::network::Buffer &buffer);

 private:
  Parent &parent_;
  tbox::network::Uart uart_;
};

}

#endif //UART_H
