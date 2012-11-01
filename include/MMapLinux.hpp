
//#include "Meta.hpp"
#include "Relation.hpp"

#include <string>

class Meta;

class MMapLinux{
    public:
        MMapLinux(const std::string file);

        void open_file();
        void set_meta(Meta& meta);
        void set_relation(Relation& relation);

    private:
        const std::string file;
        char* data;
};
