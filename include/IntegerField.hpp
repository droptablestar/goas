
#ifndef INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
#define INTEGERFIELD_8A7H8D7HAW8D7HF8AWH

class IntegerField{
    public:
        IntegerField(const int field);
        IntegerField(const IntegerField& other);
        IntegerField& operator=(const IntegerField& other);
        bool operator==(const IntegerField& other) const;
        bool operator<(const IntegerField& other) const;
        bool operator>(const IntegerField& other) const;
        bool operator!=(const IntegerField& other) const;

        void print() const;

    private:
        int field;
};

#endif //INTEGERFIELD_8A7H8D7HAW8D7HF8AWH
