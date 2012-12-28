
#ifndef INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
#define INTEGERFIELD_8A7H8D7HAW8D7HF8AWH

#include "Field.hpp"

class IntegerField:public Field{
    public:
        IntegerField(const int field);

        void print() const;
        Field* clone() const;

    private:
        const int field;
};

#endif //INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
