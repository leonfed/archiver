#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "tree.h"
#include "unarchive.h"

const int size_buf = 4000000;

unarchive::unarchive(std::string& input, std::string& output)
        : input(input)
        , output(output)
        , tree(nullptr)
        , cur(nullptr)
        , ind(0)
        , last_symbol_is_final(false)
        , check_xor(0)
        , cur_xor(0)
{}

void unarchive::doWork() {
    std::ifstream in(input, std::ios::binary);
    if (!in) {
        std::cerr << "Can't open file";
        in.close();
        return;
    }
    std::ofstream out(output, std::ios::binary);
    unsigned char buf[size_buf];
    in.read((char *)buf, sizeof(buf));
    try {
        build_tree(buf);
    } catch(std::runtime_error& e) {
        std::cerr << e.what();
        in.close();
        out.close();
        return;
    }
    std::vector<unsigned char> data;
    try {
         get_original(buf, static_cast<int>(in.gcount()), data);
    } catch(std::runtime_error& e) {
        std::cerr << e.what();
        in.close();
        out.close();
        return;
    }
    out.write((char *)data.data(), data.size());
    data.clear();
    while (in) {
        in.read((char *)buf, sizeof(buf));
        try {
            get_original(buf, static_cast<int>(in.gcount()), data);
        } catch(std::runtime_error& e) {
            std::cerr << e.what();
            in.close();
            out.close();
            return;
        }
        out.write((char *)data.data(), data.size());
        data.clear();
    }
    if (!check_correctness()) {
        std::cerr << "Incorrect data";
    }
    in.close();
    out.close();
    send("Done");
}

int unarchive::get_bit(unsigned char* a, int i) {
    int ans;
    try {
        int k = i / 8, t = 7 - i % 8;
        ans = (a[k] >> t) & 1;
    } catch(...) {
        throw std::runtime_error("incorrect data");
    }
    return ans;
}

std::shared_ptr<Node> unarchive::dfs_build_tree(unsigned char* buf, int length) {
    if (length > 64) {
        throw std::runtime_error("incorrect data");
    }
    std::shared_ptr<Node> root = std::make_shared<Node>(Node(1, nullptr, nullptr, 0));
    if (get_bit(buf, ind++)) {
        if (get_bit(buf, ind++)) {
            root->count = 0;
        } else {
            unsigned char pow = 1;
            for (int i = 0; i < 8; i++) {
                root->byte += pow * get_bit(buf, i + ind);
                pow <<= 1;
            }
            ind += 8;
        }
    } else {
        root->left = dfs_build_tree(buf, length + 1);
        root->right = dfs_build_tree(buf, length + 1);
    }
    return root;
}

void unarchive::build_tree(unsigned char *buf) {
    cur = tree = dfs_build_tree(buf, 0);
    if (ind % 8 != 0) {
        ind += (8 - ind % 8);
    }
    int k = ind / 8;
    check_xor = buf[k];
    ind += 8;
}

void unarchive::get_original(unsigned char* buf, int input_size, std::vector<unsigned char>& orig) {
    input_size = input_size * 8 - ind;
    int i = 0;
    for (; i < input_size; i++) {
        if (!cur) {
            throw std::runtime_error("incorrect data");
        }
        last_symbol_is_final = false;
        if (get_bit(buf, ind++)) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
        if (!cur->left) {
            if (cur->count != 0) {
                orig.push_back(cur->byte);
                cur_xor ^= cur->byte;
            } else {
                if (ind % 8 != 0) {
                    i += (8 - ind % 8);
                    ind += (8 - ind % 8);
                }
                last_symbol_is_final = true;
            }
            cur = tree;
        }
    }
    ind = 0;
}

bool unarchive::check_correctness() {
    return (last_symbol_is_final && (check_xor == cur_xor));
}
