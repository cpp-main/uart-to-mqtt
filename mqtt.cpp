#include "mqtt.h"

#include <tbox/base/json.hpp>
#include <tbox/util/json.h>

namespace hevake {

Mqtt::Mqtt(tbox::main::Context &ctx, Parent &parent)
 : tbox::main::Module("mqtt", ctx)
 , parent_(parent)
 , mqtt_(ctx.loop())
{ }

//! 默认参数
void Mqtt::onFillDefaultConfig(tbox::Json &js) {
  js["domain"] = "127.0.0.1";
  js["port"] = 1883;
  js["send_topic"] = "/uart_to_mqtt/send";
  js["recv_topic"] = "/uart_to_mqtt/recv";
}

bool Mqtt::onInit(const tbox::Json &js)
{
  std::string broker_domain;
  int broker_port;
  std::string recv_topic;
  tbox::mqtt::Client::Config conf;

  tbox::util::json::GetField(js, "domain", broker_domain);
  tbox::util::json::GetField(js, "port", broker_port);
  tbox::util::json::GetField(js, "client_id", conf.base.client_id);
  tbox::util::json::GetField(js, "username", conf.base.username);
  tbox::util::json::GetField(js, "passwd", conf.base.passwd);
  tbox::util::json::GetField(js, "keepalive", conf.base.keepalive);

  if (tbox::util::json::HasObjectField(js, "tls")) {
    auto &js_tls = js["tls"];

    conf.tls.enabled = true;
    tbox::util::json::GetField(js_tls, "cert_file", conf.tls.cert_file);
    tbox::util::json::GetField(js_tls, "key_file", conf.tls.key_file);
    tbox::util::json::GetField(js_tls, "ca_file", conf.tls.ca_file);
    tbox::util::json::GetField(js_tls, "ca_path", conf.tls.ca_path);
    if (!conf.tls.ca_file.empty() || !conf.tls.ca_path.empty())
      conf.tls.is_require_peer_cert = true;
  }

  tbox::util::json::GetField(js, "send_topic", send_topic_);
  tbox::util::json::GetField(js, "recv_topic", recv_topic);

  conf.base.broker.domain = broker_domain;
  conf.base.broker.port = broker_port;

  tbox::mqtt::Client::Callbacks cbs;

  cbs.connected = [this, recv_topic] {
    mqtt_.subscribe(recv_topic);
    parent_.onMqttConnected(); 
  };

  cbs.disconnected = [this] { parent_.onMqttDisconnected(); };

  cbs.message_recv = [this] (int, const std::string &, const void *payload_ptr, int payload_len, int, bool) {
    parent_.onMqttRecv(payload_ptr, payload_len);
  };

  if (!mqtt_.initialize(conf, cbs))
    return false;

  return true;
}

bool Mqtt::onStart() { return mqtt_.start(); }

void Mqtt::onStop() { mqtt_.stop(); }

void Mqtt::onCleanup() { mqtt_.cleanup(); }

void Mqtt::send(const void *data_ptr, size_t data_size) {
  mqtt_.publish(send_topic_, data_ptr, data_size);
}

}
