#ifndef RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
#define RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG

class RawStringField{
    public:
        RawStringField(const unsigned int size);
        ~RawStringField();
        RawStringField(const RawStringField& other);
        RawStringField& operator=(RawStringField other);
        RawStringField(RawStringField&& other);

        void print() const;
        char* raw_ptr() const;

    private:
        void swap(RawStringField& a, RawStringField& b);

    private:
        unsigned int size;
        char* field;
};

#endif //RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
