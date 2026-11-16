#pragma once

#include <array>
#include <cstdint>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace huftre
{
using Byte  = std::uint8_t;           //uint8_t
using Count = std::uint64_t;          //uint64_t

template <typename T>
struct Node
{
    T        data;
    Count    freq;
    Node<T>* left;
    Node<T>* right;
    bool     isLeaf;

    Node(T _data, Count _freq)
        : data(_data), freq(_freq), left(nullptr), right(nullptr), isLeaf(true) {}

    Node(Node* _left, Node* _right)
        : data(), freq(_left->freq + _right->freq),
        left(_left), right(_right), isLeaf(false) {}

    Node(const Node&)            = delete;
    Node& operator=(const Node&) = delete;
};

//最小堆比较器
template <typename T>
struct MinComp {
    bool operator()(const Node<T>* a, const Node<T>* b) const {
        return a->freq > b->freq;
    }
};

//内存释放
template <typename T>
void freeTree(Node<T>* root)
{
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

//通用建树
template <typename T>
Node<T>* buildHuffmanTree(const std::unordered_map<T, int>& freqmap)
{
    std::priority_queue<Node<T>*, std::vector<Node<T>*>, MinComp<T>> pq;

    try {
        for (const auto& kv : freqmap) {
            if (kv.second > 0)
                pq.push(new Node<T>(kv.first,
                                    static_cast<Count>(kv.second)));
        }
        if (pq.empty()) return nullptr;

        while (pq.size() > 1) {
            Node<T>* a = pq.top(); pq.pop();
            Node<T>* b = pq.top(); pq.pop();
            pq.push(new Node<T>(a, b));
        }
        Node<T>* root = pq.top();
        pq.pop();
        return root;
    } catch (...) {
        while (!pq.empty()) { delete pq.top(); pq.pop(); }
        throw;
    }
}

//字节频率表建树
template <typename CountT>
Node<Byte>* buildTree(const std::array<CountT, 256>& freq)
{
    using NodePtr = Node<Byte>*;
    std::priority_queue<NodePtr, std::vector<NodePtr>, MinComp<Byte>> pq;

    try {
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 0)
                pq.push(new Node<Byte>(static_cast<Byte>(i),
                                       static_cast<Count>(freq[i])));
        }
        if (pq.empty()) return nullptr;

        while (pq.size() > 1) {
            NodePtr a = pq.top(); pq.pop();
            NodePtr b = pq.top(); pq.pop();
            pq.push(new Node<Byte>(a, b));
        }
        NodePtr root = pq.top();
        pq.pop();
        return root;
    } catch (...) {
        while (!pq.empty()) { delete pq.top(); pq.pop(); }
        throw;
    }
}

//生成前缀码
inline void generateCodes(const Node<Byte>* root,
                          const std::string& code,
                          std::unordered_map<Byte, std::string>& codes)
{
    if (!root) return;

    if (!root->left && !root->right) {               // 叶子
        codes[root->data] = code.empty() ? "0" : code;
        return;
    }
    generateCodes(root->left,  code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

//编码
inline std::string encode(const std::string& text,
                          const std::unordered_map<Byte, std::string>& codes)
{
    std::string result;
    result.reserve(text.size() * 4);

    for (char ch : text) {
        auto it = codes.find(static_cast<Byte>(ch));
        if (it == codes.end())
            throw std::runtime_error("encode: symbol not in code table");
        result += it->second;
    }
    return result;
}

//解码
inline std::string decode(const std::string& bits, const Node<Byte>* root)
{
    if (!root)
        throw std::runtime_error("decode: empty tree");

    std::string result;
    if (!root->left && !root->right) {
        for (char b : bits) {
            if (b != '0')
                throw std::runtime_error("decode: invalid bit (single-symbol tree)");
            result += static_cast<char>(root->data);
        }
        return result;
    }

    const Node<Byte>* cur = root;
    for (char b : bits) {
        if      (b == '0') cur = cur->left;
        else if (b == '1') cur = cur->right;
        else               throw std::runtime_error("decode: non-binary bit");

        if (!cur)
            throw std::runtime_error("decode: corrupt bitstream");

        if (!cur->left && !cur->right) {
            result += static_cast<char>(cur->data);
            cur = root;
        }
    }

    if (cur != root)
        throw std::runtime_error("decode: truncated bitstream");

    return result;
}

} // namespace huftre