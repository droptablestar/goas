#ifndef METAPOPULATOR_98QE0F9HW0E9F8HQWEHF8QHWFYG
#define METAPOPULATOR_98QE0F9HW0E9F8HQWEHF8QHWFYG

#include "Constants.hpp"

#include <vector>
#include <string>

class Meta;

class MetaBasicPopulator{
    public:
        MetaBasicPopulator(Meta& meta);

        void columns(const unsigned short columns);
        void rows(const unsigned int rows);
        void colum_names();
        void column_names_and_types(std::string field);
        void column_types();

    private:
        Meta& meta;
        std::vector<std::string> name_container;
        std::vector<TYPES> type_container;
};

#endif


