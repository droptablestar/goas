#ifndef RELATION_Q9HF9QWHEF98WHEF9
#define RELATION_Q9HF9QWHEF98WHEF9

#include "Meta.hpp"

#include <vector>
#include <string>

class Record;

class Relation{
    public:
        Relation();
        ~Relation();

        void add_record(Record* rec);
        Meta* get_meta();
        void print() const;
        void set_size();
        void sort_ascendant(std::vector<unsigned int>& indexes);
        void sort_descendant(std::vector<unsigned int>& indexes);
        void project(std::vector<unsigned int>& indexes);

    private:
        std::vector<Record*> records;
        Meta meta;
};

#endif //RELATION_Q9HF9QWHEF98WHEF9
