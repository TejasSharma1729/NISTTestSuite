#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(void) {
    ifstream in("random", ios::binary);
    ofstream add_result("add_results", ios::binary);
    ofstream sub_result("sub_results", ios::binary);
    ofstream mul_result("mul_results", ios::binary);
    ofstream div_result("div_results", ios::binary);
    ofstream mod_result("mod_results", ios::binary);
    ofstream xor_result("xor_results", ios::binary);
    ofstream and_result("and_results", ios::binary);
    ofstream or_result("or_results", ios::binary);
    vector<char> a(8), b(8);
    while (in.read(&a[0], 8) && in.read(&b[0], 8)) {
        size_t a_val = *reinterpret_cast<size_t*>(&a[0]);
        size_t b_val = *reinterpret_cast<size_t*>(&b[0]);
        size_t c_val = a_val + b_val;
        add_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val - b_val;
        sub_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val * b_val;
        mul_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val / b_val;
        div_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val % b_val;
        mod_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val ^ b_val;
        xor_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val & b_val;
        and_result.write(reinterpret_cast<char*>(&c_val), 8);
        c_val = a_val | b_val;
        or_result.write(reinterpret_cast<char*>(&c_val), 8);
    }
}
