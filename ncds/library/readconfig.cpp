#include <tuple>
#include <utility>

#include <librdkafka/rdkafkacpp.h>

#include "readconfig.h"

namespace {

  template <typename type_t, typename tuple_t>
  struct index_t;

  template <typename type_t, typename... types_t>
  struct index_t<type_t, std::tuple<type_t, types_t...>> {
      static const std::size_t value = 0;
  };

  template <typename type_t, typename u_t, typename... types_t>
  struct index_t<type_t, std::tuple<u_t, types_t...>> {
      static const std::size_t value = 1 + index_t<type_t, std::tuple<types_t...>>::value;
  };

  static const auto names = std::make_tuple(
    std::pair<const RdKafka::DeliveryReportCb*, std::string>(0, "dr_cb"),
    std::pair<const RdKafka::OAuthBearerTokenRefreshCb*, std::string>(0, "oauthbearer_token_refresh_cb"),
    std::pair<const RdKafka::EventCb*, std::string>(0, "event_cb"),
    std::pair<const RdKafka::Conf*, std::string>(0, "default_topic_conf"),
    std::pair<const RdKafka::PartitionerCb*, std::string>(0, "partitioner_cb"),
    std::pair<const RdKafka::PartitionerKeyPointerCb*, std::string>(0, "partitioner_key_pointer_cb"),
    std::pair<const RdKafka::SocketCb*, std::string>(0, "socket_cb"),
    std::pair<const RdKafka::OpenCb*, std::string>(0, "open_cb"),
    std::pair<const RdKafka::RebalanceCb*, std::string>(0, "rebalance_cb"),
    std::pair<const RdKafka::OffsetCommitCb*, std::string>(0, "offset_commit_cb"),
    std::pair<const RdKafka::SslCertificateVerifyCb*, std::string>(0, "ssl_cert_verify_cb")
  );

  template <typename param_t>
  static const std::string& get_name(const param_t*) {
    return std::get<std::pair<const param_t*, std::string>>(names).second;
  }

} /* namespace */

namespace kf {

  const config_t::strings_t config_t::glogal = {
    "builtin.features", "client.id", "metadata.broker.list", "bootstrap.servers", "message.max.bytes",
    "message.copy.max.bytes", "receive.message.max.bytes", "max.in.flight.requests.per.connection",
    "max.in.flight", "metadata.request.timeout.ms", "topic.metadata.refresh.interval.ms",
    "metadata.max.age.ms", "topic.metadata.refresh.fast.interval.ms", "topic.metadata.refresh.fast.cnt",
    "topic.metadata.refresh.sparse", "topic.blacklist", "debug", "socket.timeout.ms",
    "socket.blocking.max.ms", "socket.send.buffer.bytes", "socket.receive.buffer.bytes",
    "socket.keepalive.enable", "socket.nagle.disable", "socket.max.fails", "broker.address.ttl",
    "broker.address.family", "reconnect.backoff.jitter.ms", "statistics.interval.ms",
    "enabled_events", "log_level", "log.queue", "log.thread.name", "log.connection.close",
    "opaque", "default_topic_conf", "internal.termination.signal", "api.version.request",
    "api.version.request.timeout.ms", "api.version.fallback.ms", "broker.version.fallback",
    "security.protocol", "ssl.cipher.suites", "ssl.curves.list", "ssl.sigalgs.list",
    "ssl.key.location", "ssl.key.password", "ssl.certificate.location", "ssl.ca.location",
    "ssl.crl.location", "ssl.keystore.location", "ssl.keystore.password", "sasl.mechanisms",
    "sasl.mechanism", "sasl.kerberos.service.name", "sasl.kerberos.principal",
    "sasl.kerberos.kinit.cmd", "sasl.kerberos.keytab", "sasl.kerberos.min.time.before.relogin",
    "sasl.username", "sasl.password", "plugin.library.paths", "group.id", "partition.assignment.strategy",
    "session.timeout.ms", "heartbeat.interval.ms", "group.protocol.type", "coordinator.query.interval.ms",
    "enable.auto.commit", "auto.commit.interval.ms", "enable.auto.offset.store", "queued.min.messages",
    "queued.max.messages.kbytes", "fetch.wait.max.ms", "fetch.message.max.bytes", "max.partition.fetch.bytes",
    "fetch.max.bytes", "fetch.min.bytes", "fetch.error.backoff.ms", "offset.store.method",
    "enable.partition.eof", "check.crcs", "queue.buffering.max.messages", "queue.buffering.max.kbytes",
    "queue.buffering.max.ms", "linger.ms", "message.send.max.retries", "retries", "retry.backoff.ms",
    "queue.buffering.backpressure.threshold", "compression.codec", "compression.type", "batch.num.messages",
    "delivery.report.only.error"
  };

  const config_t::strings_t config_t::topic = {
    "request.required.acks", "acks", "request.timeout.ms", "message.timeout.ms", "queuing.strategy",
    "produce.offset.report", "partitioner", "partitioner_cb", "msg_order_cmp", "opaque",
    "compression.codec", "compression.type", "compression.level", "auto.commit.enable",
    "enable.auto.commit", "auto.commit.interval.ms", "auto.offset.reset", "offset.store.path",
    "offset.store.sync.interval.ms", "offset.store.method", "consume.callback.max.messages"
  };

  config_t::config_t(const config_t::type_t& value)
      : m_config(RdKafka::Conf::create(value == e_global ? RdKafka::Conf::CONF_GLOBAL : RdKafka::Conf::CONF_TOPIC))
      , m_param(value == e_global ? glogal : topic) {
  }

  void config_t::read_config(const get_property_t& get_property, const error_t& err_notify) {
    std::string err;
    for(const auto& it : m_param)
      if(const auto& tmp = get_property(it))
        if(RdKafka::Conf::CONF_OK != m_config->set(it, *tmp, err))
          err_notify(err);
  }

  void config_t::set(RdKafka::DeliveryReportCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::EventCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::Conf* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::PartitionerCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::PartitionerKeyPointerCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::SocketCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::OpenCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::RebalanceCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::OffsetCommitCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::SslCertificateVerifyCb* value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err));
      err_notify(err);
  }

  void config_t::set(RdKafka::CertificateType cert_type, RdKafka::CertificateEncoding cert_enc,
      const config_t::buffer_t& value, const error_t& err_notify) {
    std::string err;
    if(RdKafka::Conf::CONF_OK != m_config->set_ssl_cert(cert_type, cert_enc, value.data(), value.size(), err));
      err_notify(err);
  }

  const RdKafka::Conf& config_t::get_config() const {
    return *m_config.get();
  }

} /* namespace kf */
