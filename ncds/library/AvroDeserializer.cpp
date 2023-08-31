#include <memory>
#include <cassert>

#include <avro/Generic.hh>
#include <avro/Decoder.hh>
#include <avro/Specific.hh>

#include <librdkafka/rdkafkacpp.h>

#include "AvroDeserializer.h"


//********************************************************
//                  Avro Deserializer
//********************************************************

AvroDeserializer::AvroDeserializer(avro::ValidSchema schema) : schema(schema) {}

avro::GenericRecord AvroDeserializer::decode(const uint8_t *data, size_t len) {
    std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(data, len);

    avro::DecoderPtr d = avro::binaryDecoder();
    d->init(*in);

    avro::GenericDatum datum(this->schema);

    avro::decode(*d, datum);

    assert(datum.type() == avro::AVRO_RECORD);
    avro::GenericRecord r = datum.value<avro::GenericRecord>();
    return r;
}


//********************************************************
//                     Consume Msg
//********************************************************
namespace ncds {
    DeserializeMsg::DeserializeMsg(avro::ValidSchema schema) : schema(schema) {}

    avro::GenericRecord DeserializeMsg::deserialize_msg(RdKafka::Message &message) {
        if (message.err() != RdKafka::ERR_NO_ERROR) {
            throw std::runtime_error("There was an error deserializing the message: " + message.errstr());
        }

        uint8_t *data = static_cast<uint8_t *>(message.payload());
        size_t len = message.len();

        AvroDeserializer deserializer(this->schema);

        avro::GenericRecord r = deserializer.decode(data, len);

        return r;
    }
} // namespace ncds