#ifndef RELATION_Q9HF9QWHEF98WHEF9
#define RELATION_Q9HF9QWHEF98WHEF9

#include "Meta.hpp"
#include "Record.hpp"
#include "Field.hpp"

#include <vector>
#include <string>

#define INT 0
#define STRING 1

class Relation{
    public:
        Relation();
        ~Relation();

        void add_record(Record* rec);
        Meta& get_meta();
        void print() const;
        void set_size();

    private:
        std::vector<Record*> records;
        Meta meta;
};

#endif //RELATION_Q9HF9QWHEF98WHEF9
