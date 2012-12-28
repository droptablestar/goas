#ifndef RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
#define RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG

#include "Field.hpp"

class RawStringField:public Field{
    public:
        RawStringField(const unsigned int size);
        ~RawStringField();

        void print() const;
        char* raw_ptr() const;
        Field* clone() const;

    private:
        char* _field;
        const unsigned int size;
};

#endif //RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
