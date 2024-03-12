#include <string>
#include <vector>
#pragma once

using namespace std;

class Scheme : public vector<string> {
    public:
        Scheme(vector<string> names) : vector<string>(names) {}
};