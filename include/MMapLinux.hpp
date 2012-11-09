#ifndef MMAPLINUX_93R8JG9EW8JRG9WEJ8RG98JWER9G8J
#define MMAPLINUX_93R8JG9EW8JRG9WEJ8RG98JWER9G8J


#include <string>

class Meta;
class Relation;

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

#endif //MMAPLINUX_93R8JG9EW8JRG9WEJ8RG98JWER9G8J
