#include "print_records.h"

void print_records(std::vector<avro::GenericRecord> &records) {
    for (auto &record : records) {
        std::cout << "Message name: " << record.schema()->name().simpleName() << std::endl;
        for (size_t i = 0; i < record.fieldCount(); i++) {
            avro::GenericDatum datum = record.fieldAt(i);
            std::cout << record.schema()->nameAt(i) << ": ";
            if (datum.type() == avro::AVRO_DOUBLE) {
                double num = datum.value<double>();
                std::cout << num << std::endl;
            } else if (datum.type() == avro::AVRO_LONG) {
                int64_t num = datum.value<int64_t>();
                std::cout << num << std::endl;
            } else if (datum.type() == avro::AVRO_INT) {
                int num = datum.value<int>();
                std::cout << num << std::endl;
            } else if (datum.type() == avro::AVRO_STRING) {
                std::string str = datum.value<std::string>();
                std::cout << str << std::endl;
            }
        }
    }
}
