#ifndef UNARCHIVE_H
#define UNARCHIVE_H

#include <QObject>
#include "tree.h"
#include <vector>
#include <string>

struct unarchive : public QObject
{
    Q_OBJECT

public:
    unarchive(std::string& input, std::string& output);

public slots:
    void doWork();

signals:
    void send(std::string);

private:

    //build huffman tree
    void build_tree(unsigned char* buf);

    //write original data to vector<unsigned char>decode
    void get_original(unsigned char* buf, int size_buf, std::vector<unsigned char>& decode);

    //check_correctness of input data
    bool check_correctness();


    int get_bit(unsigned char* buf, int index);
    std::shared_ptr<Node> dfs_build_tree(unsigned char* buf, int length);

    std::string& input;
    std::string& output;
    std::shared_ptr<Node> tree;
    std::shared_ptr<Node> cur;
    int ind;
    bool last_symbol_is_final;
    unsigned char check_xor, cur_xor;
};

#endif // UNARCHIVE_H
