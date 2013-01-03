
#ifndef RECORD_W98HRG9WEH8RG9W8HERG98WHERG
#define RECORD_W98HRG9WEH8RG9W8HERG98WHERG

#include "IntegerField.hpp"
#include "RawStringField.hpp"

#include <vector>

class Meta;

class Record{
    public:
        Record(const unsigned int size, Meta& meta);

        void add(RawStringField& field);
        void add(IntegerField& field);
        void print() const;

    private:
        std::vector<IntegerField> container_IF;
        std::vector<RawStringField> container_SF;
        const Meta& meta;
};

#endif //RECORD_W98HRG9WEH8RG9W8HERG98WHERG


