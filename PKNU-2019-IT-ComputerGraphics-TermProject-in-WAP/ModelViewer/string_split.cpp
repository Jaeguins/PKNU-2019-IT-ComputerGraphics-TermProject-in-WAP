#include <vector>
#include <sstream>
#include "string_split.h"

namespace std {
    vector<string> split(string str, char delimiter) {
        vector<string> internal;
        stringstream ss(str);
        string temp;

        while (getline(ss, temp, delimiter)) {
            internal.push_back(temp);
        }

        return internal;
    }
}
