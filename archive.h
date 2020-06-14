#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <iostream>
#include <vector>
#include <string>
#include <debug/vector>
#include "tree.h"

struct archive {


public:
    archive(std::string& input, std::string& output);

    void doWork();

private:
    //count symbols and check_xor
    void count(unsigned char* buf, int size_buf);

    //generate huffman tree
    void generate_code();

    //write code of tree and check_xor to vector<unsigned char>code
    void get_tree_code_and_check_xor(std::vector<unsigned char>& code);

    //write code of buf to vector<unsigned char>code
    void get_data_code(unsigned char* buf, int size_buf, std::vector<unsigned char>& code);

    void dfs_fill_byte_code(std::pair<unsigned long long, int>& , std::shared_ptr<Node>);
    void convert_bool_to_char(std::vector<bool>& code_bool, std::vector<unsigned char>& code_char);
    void convert_long_to_char(std::vector<std::pair<unsigned long long, int>>& code_long, std::vector<unsigned char>& code_char);

    std::string input;
    std::string output;
    std::vector<unsigned long long> cnt;
    std::shared_ptr<Node> tree;
    std::vector<std::pair<unsigned long long, int>> byte_code;
    std::pair<unsigned long long, int> final_byte;
    unsigned char check_xor;
};

#endif // ARCHIVE_H
