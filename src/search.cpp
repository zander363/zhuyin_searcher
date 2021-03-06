#include <codecvt>
#include <locale>
#include <iostream>
#include <fstream>

#include <unordered_map>
#include "util.h"
#include "methods.h"


class Util util;

int main(int argc, char* argv[]) {
    std::wstring line;
    std::size_t found;
    std::setlocale(LC_ALL, "");
    const std::locale utf8_locale
        = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

    if (argc < 2) {
        std::cout << "usage : ./search <path/to/BreachCompilation/data\n\te.g. ./search ../BreachCompilation/data/y/z" << std::endl;
        exit(255);
    }

    std::wifstream file;
    file.open(argv[1]);
    if (!file.is_open()) {
        std::cout << argv[1] << " does not exist!" << std::endl;
        exit(255);
    }
    file.imbue(utf8_locale);

#ifdef NOTYPE
    class NoType* noType = new NoType();
#endif

#ifdef ONLYCHINESE
    class OnlyChinese* onlyChinese = new OnlyChinese();
#endif
    
    while (getline(file, line)) {
        found = line.find_first_of(L"@");
        if (found == std::wstring::npos) {
            continue;
        }
        found = line.find_first_of(L":;", found+1);
        if (found == std::string::npos) {
            continue;
        }
        line = line.substr(found+1);

#ifdef NOTYPE
        noType->process(line);
#endif

#ifdef ONLYCHINESE
        onlyChinese->process(line);
#endif

    }

#ifdef NOTYPE
    noType->print();
#endif

#ifdef ONLYCHINESE
    onlyChinese->print();
#endif

}
