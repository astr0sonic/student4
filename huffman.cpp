#include "huffman.h"
#include <map>
#include <queue>
#include <string>

struct Node {
	char inf;
	int arr;
	Node* l;
	Node* r;
	Node(char ch, int f) : inf(ch), arr(f), l(nullptr), r(nullptr) {}
};

struct low_pri {
	bool operator()(Node* a, Node* b) {
		return a->arr > b->arr;
	}
};

void encodeHelper(Node* node, std::string code, std::map<char, std::string>& codes) {
	if (!node) return;
	if (node->inf != '%') codes[node->inf] = code;
	encodeHelper(node->l, code + "0", codes);
	encodeHelper(node->r, code + "1", codes);
}

std::string encode(const std::string& str) {
	std::map<char, int> arr;
	std::priority_queue<Node*, std::vector<Node*>, low_pri> queue;
	std::map<char, std::string> codes;
	std::string code;
	std::string encoded = "";

	for (char ch : str) arr[ch]++;
	for (const auto& entry : arr) queue.push(new Node(entry.first, entry.second));

	while (queue.size() > 1) {
		Node* l = queue.top();
		queue.pop();
		Node* r = queue.top();
		queue.pop();
		Node* tree = new Node('%', l->arr + r->arr);
		tree->l = l;
		tree->r = r;
		queue.push(tree);
	}

	Node* root = queue.top();
	encodeHelper(root, code, codes);
	for (char ch : str) encoded += codes[ch];
	return encoded;
}

std::string decode(const std::string& encoded, std::map<char, std::string>& codes) {
	std::string decoded = "";
	std::string currCode = "";
	for (char ch : encoded) {
		currCode += ch;
		for (const auto& entry : codes) {
			if (entry.second == currCode) {
				decoded += entry.first;
				currCode = "";
				break;
			}
		}
	}
	return decoded;
}