
#ifndef FIELD_8WHRG9WE8HRG9EWHRGNKJDNSGNK
#define FIELD_8WHRG9WE8HRG9EWHRGNKJDNSGNK

class Field{
    public:
        Field(){};
        virtual ~Field(){};

        virtual void print() const = 0;
        virtual Field* clone() const = 0;
};

#endif //FIELD_8WHRG9WE8HRG9EWHRGNKJDNSGNK
