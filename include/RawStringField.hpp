#ifndef RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
#define RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG

class RawStringField{
    public:
        RawStringField(const unsigned int size);
        ~RawStringField();
        RawStringField(const RawStringField& other);
        RawStringField& operator=(RawStringField other);
        RawStringField(RawStringField&& other);
        bool operator==(const RawStringField& other) const;
        bool operator!=(const RawStringField& other) const;

        void print() const;
        char* raw_ptr() const;
        unsigned int length() const;

    private:
        void swap(RawStringField& a, RawStringField& b);

    private:
        unsigned int size;
        char* field;
};

#endif //RAWSTRINGFIELD_9S8RY987YG8WH7EG8E7WHG87HEW8R7HG
