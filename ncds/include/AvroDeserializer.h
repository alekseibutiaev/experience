#include <avro/Generic.hh>
#include <avro/Decoder.hh>
#include <librdkafka/rdkafkacpp.h>

/**
 * @ingroup internal
 * @brief Deserializes RdKafka::Message types and returns the message as a Generic Record
 */
namespace ncds {

    class DeserializeMsg {
    public:
        /**
        * Initializes the deserializer with the appropriate schema.
        * @param schema: A ValidSchema
        */
        explicit DeserializeMsg(avro::ValidSchema schema);

        /**
        * Deserializes a message
        * @param message: A librdkafka Message object
        * @return an avro GenericRecord
        */
        avro::GenericRecord deserialize_msg(RdKafka::Message &message);

    private:
        avro::ValidSchema schema;
    };
} // namespace ncds

/**
\cond HIDE_FROM_DOCUMENTATION
*/
    class AvroDeserializer {
    public:
        avro::ValidSchema schema;

        AvroDeserializer(avro::ValidSchema schema);

        avro::GenericRecord decode(const uint8_t *data, size_t len);
    };
/**
 * \endcond
 */
