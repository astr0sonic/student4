#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <bitset>
using uchar = unsigned char; //psevdonim chtobi ne picat' mnogo

class Node {
public:
	using pointer = std::shared_ptr<Node>;
	pointer l{ nullptr };
	pointer r{ nullptr };
	pointer parent{ nullptr };

	Node() = default;
	Node(uchar uch, int f) : ch(uch), arr(f) {}
	Node(const std::string& n, int f) : name(n), arr(f) {}

	friend std::ostream& operator<<(std::ostream& os, const Node& node);
	int get_arr() const {
		return arr;
	}
	void set_arr(int a) {
		arr = a;
	}

	std::string code() const {
		return code_string;
	}
	void code(const std::string& c) {
		code_string = c;
	}

	std::string get_name() const {
		if (ch == 0) {
			return name;
		}
		else return std::string(1, static_cast<char>(ch));
	}
	uchar get_byte() const {
		return ch;
	}

private:
	std::string name{ "" };
	uchar ch{ 0 };
	int arr{ 0 }; //inizializise for no trash
	std::string code_string{ "" };
};

class low_pri {
public:
	bool operator()(const Node::pointer& l, const Node::pointer& r) const {
		return l->get_arr() > r->get_arr();
	}
};

std::ostream& operator<<(std::ostream& os, const Node& node) {
	return os << "[" << node.get_name() << "] = " << node.arr;
}

void read_file(const std::string& filename, std::vector<int>& arr) {
	std::ifstream ifs(filename, std::ifstream::binary);
	while (!ifs.eof()) {
		char ch;
		ifs.read(&ch, 1);
		arr[static_cast<unsigned char>(ch)]++;
	}
}

std::string message2code(const std::string& filename, const std::vector<std::string>& codes) {
	std::string msg{ "" };
	std::ifstream ifs(filename, std::ifstream::binary);
	while (true) {
		char ch;
		ifs.read(&ch, 1);
		if (ifs.eof()) break;
		msg += codes[static_cast<unsigned char>(ch)];
	}
	return msg;
}

void make_code(Node::pointer& node, std::string str, std::vector<std::string>& codes) {
	if (node->l != nullptr) {
		make_code(node->l, str + "0", codes);
	}
	if (node->r != nullptr) {
		make_code(node->r, str + "1", codes);
	}
	if (node->l == nullptr && node->r == nullptr) {
		node->code(str);
		codes[node->get_byte()] = str;
	}
}

void fill_queue(std::vector<int>& arr, std::priority_queue<Node::pointer, std::vector<Node::pointer>, low_pri>& queue) {
	for_each(arr.begin(), arr.end(), [byte = uchar{ 0 }, &queue](const auto& value) mutable {
		if (value != 0) {

			Node::pointer node = std::make_shared<Node>(byte, value);
			queue.push(node);
		}
		byte++;
		});
}

void build_tree(std::priority_queue<Node::pointer, std::vector<Node::pointer>, low_pri>& queue) {
	while (queue.size() > 1)
	{
		Node::pointer x = queue.top();
		queue.pop();
		Node::pointer y = queue.top();
		queue.pop();
		std::string name = x->get_name() + y->get_name();
		Node::pointer z = std::make_shared<Node>(name, x->get_arr() + y->get_arr());
		z->l = x;
		z->r = y;

		x->parent = z;
		y->parent = z;
		queue.push(z);
	}
}

void reading_decoding_file(std::string& filename, std::vector<int>& arr, std::string& message) {
	std::string new_file = filename + ".hff";
	std::ifstream ifs(filename, std::ifstream::binary);
	uchar count = 0;
	ifs.read(reinterpret_cast<char*>(&count), sizeof count);
	int i = 0;
	while (i < count) {
		uchar ch;
		ifs.read(reinterpret_cast<char*>(&ch), sizeof ch);
		int f = 0;
		ifs.read(reinterpret_cast<char*>(&f), sizeof f);
		arr[ch] = f;
		++i;
	}
	int byte_count = 0;
	uchar modulo = 0;
	ifs.read(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
	ifs.read(reinterpret_cast<char*>(&modulo), sizeof modulo);
	i = 0;
	for (; i < byte_count; i++) {
		uchar byte;
		ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
		std::bitset<CHAR_BIT> b(byte);
		message += b.to_string();
	}
	if (modulo > 0) {
		uchar byte;
		std::bitset<CHAR_BIT> b(byte);
		message += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
	}
}

void make_char(const Node::pointer& root, const std::string& message, std::string& text) {
	Node::pointer node = root;
	auto found_the_letter = [&text, &root](Node::pointer& n) {
		text += n->get_byte();
		n = root;
		};

	for (size_t i = 0; i < message.size(); ++i) {
		char ch = message[i];
		if (ch == '0') {
			if (node->l != nullptr) {
				node = node->l;
				if (node->l == nullptr && node->r == nullptr) {
					found_the_letter(node);
				}
			}
		}
		else if (ch == '1') {
			if (node->r != nullptr) {
				node = node->r;
				if (node->l == nullptr && node->r == nullptr) {
					found_the_letter(node);
				}
			}
		}
	}
}


int main(int argc, char** argv) {
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	string result = "";
	string filename = inputFileName;
	int len = inputFileName.length();
	bool isDecoding = static_cast<int>(inputFileName[len - 5]) - static_cast<int>('0') >= 4;
	if (isDecoding) {
		std::vector<int> arr2(256, 0);
		std::string message2 = "";
		reading_decoding_file(inputFileName, arr2, message2);

		std::priority_queue<Node::pointer, std::vector<Node::pointer>, low_pri> queue2;
		fill_queue(arr2, queue2);
		build_tree(queue2);

		Node::pointer root2 = queue2.top();
		std::string text = "";
		make_char(root2, message2, text);
		std::cout << message2;
		result = message2;
	}
	else {
		std::vector<int> arr(256, 0);
		read_file(filename, arr);
		std::priority_queue<Node::pointer, std::vector<Node::pointer>, low_pri> queue;
		fill_queue(arr, queue);
		build_tree(queue);

		std::vector<std::string> codes(256, "");
		Node::pointer root = queue.top();
		make_code(root, "", codes);
		std::string message = message2code(filename, codes);
		result = message;
	}

	ofstream out(outputFileName);
	out << result << std::endl;
	out.close();

	return 0;

}