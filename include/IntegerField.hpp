
#ifndef INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
#define INTEGERFIELD_8A7H8D7HAW8D7HF8AWH

#include "Field.hpp"

class IntegerField:public Field{
    public:
        IntegerField(const int field);
        IntegerField(const IntegerField& other);
//        IntegerField& operator=(const IntegerField& other);

        void print() const;
        Field* clone() const;

    private:
        int field;
};

#endif //INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
