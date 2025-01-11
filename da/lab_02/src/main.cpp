#include <fstream>
#include <algorithm>
#include <iostream>
#include <cinttypes>

template<class T>
class TQueue final {
    public:
        TQueue() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        ~TQueue() {
            while(head) {
                TQueueNode* x = head->next;
                delete head;
                head = x;
            }
        }

        bool Push(const T& v) {
            TQueueNode* x;
            try{
                x = new TQueueNode(v);
            } catch(std::bad_alloc const&) {
                return false;
            }
            
            if(IsEmpty()) {
                head = x;
                tail = x;
                size++;
                return true;
            }
            
            tail->next = x;
            tail = x;
            size++;
            return true;
        }

        T Pop() {
            TQueueNode* x = head;
            head = x->next;
            size--;
            T t = x->data;
            delete x;
            return t;
        }

        bool IsEmpty() const {
            return (size == 0);
        }

    private:
        struct TQueueNode final {
            T data;
            TQueueNode* next = nullptr;

            TQueueNode(const T& v): data(v) {}
        };

        TQueueNode* head;
        TQueueNode* tail;
        size_t size;
};

struct TKeyValue final {
    std::string key;
    uint64_t value;

    TKeyValue(std::string k, const uint64_t v): value(v) {
        key = std::move(k);
    }
    
    TKeyValue(const TKeyValue& other) {
        key = std::move(other.key);
        value = other.value;
    }

    friend bool operator< (const TKeyValue& lhs, const TKeyValue& rhs) {
        return lhs.key < rhs.key;
    }

    friend bool operator> (const TKeyValue& lhs, const TKeyValue& rhs) {
        return lhs.key > rhs.key;
    }

    friend bool operator== (const TKeyValue& lhs, const TKeyValue& rhs) {
        return lhs.key == rhs.key;
    }
};

template <class T>
class TAVLTree {
    public:
        TAVLTree() {
            root = nullptr;
        }

        TAVLTree& operator=(TAVLTree&& other) {
            root = other.root;
            other.root = nullptr;
            return *this;
        }

        ~TAVLTree() {
            clear(root);
        }

        const T& TryFind(const T& v) const {
            TNode* t = find(root, v);
            if(t == nullptr) {
                throw std::runtime_error("Value not found");
            }
            return t->value;
        }

        bool Insert(const T& v) {
            TNode* t = find(root, v);
            if(t != nullptr) {
                return false;
            }
            root = insert(root, v);
            rebalance(root);
            return true;
        }

        bool Remove(const T& v) {
            TNode* t = find(root, v);
            if(t == nullptr) {
                return false;
            }
            root = remove(root, v);
            rebalance(root);
            return true;
        }

        void Clear() {
            clear(root);
            root = nullptr;
        }

    protected:
        struct TNode final {
            T value;

            int8_t height = 1;
            TNode* left = nullptr;
            TNode* right = nullptr;
        };

        TNode* root;

        static void calculate_height(TNode* node) {
            int8_t lh = (node->left) ? node->left->height : 0;
            int8_t rh = (node->right) ? node->right->height : 0;
            node->height = 1 + std::max(lh, rh);
        }

        static int8_t update_height(TNode* node) {
            if(node == nullptr) {
                return 0;
            }
            node->height = 1 + std::max(update_height(node->left), update_height(node->right));
            return node->height;
        }

        static int8_t calculate_bfactor(TNode* node) {
            if(node == nullptr) {
                return 0;
            }
            int8_t lh = (node->left) ? node->left->height : 0;
            int8_t rh = (node->right) ? node->right->height : 0;
            return rh - lh;
        }

        static TNode* rotate_left(TNode* node) {
            TNode* tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            update_height(node);
            update_height(tmp);
            return tmp;
        }

        static TNode* rotate_right(TNode* node) {
            TNode* tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            update_height(node);
            update_height(tmp);
            return tmp;
        }

        static TNode* rebalance(TNode* node) {
            int8_t bf = calculate_bfactor(node);
            if(bf == 2) {
                if(calculate_bfactor(node->right) < 0) {
                    node->right = rotate_right(node->right);
                }
                return rotate_left(node);
            } else if(bf == -2) {
                if(calculate_bfactor(node->left) > 0) {
                    node->left = rotate_left(node->left);
                }
                return rotate_right(node);
            }

            return node;
        } 

        static TNode* find(TNode* node, const T& v) {
            if(node == nullptr) {
                return nullptr;
            }

            if(node->value == v) {
                return node;
            }

            if(v > node->value) {
                return find(node->right, v);
            } else {
                return find(node->left, v);
            }
        }

        static TNode* find_min(TNode* node) {
            if(node == nullptr) {
                return nullptr;
            }

            while(node->left) {
                node = node->left;
            }
            return node;
        }

        static TNode* remove_min(TNode* node) {
            if(node->left == nullptr) {
                return node->right;
            }
            node->left = remove_min(node->left);

            calculate_height(node);
            return rebalance(node);
        }

        static TNode* insert(TNode* node, const T& v) {
            if(node == nullptr) {
                return new TNode(v);
            }

            if(node->value == v) {
                return node;
            }

            if(v > node->value) {
                node->right = insert(node->right, v);
                
            } else {
                node->left = insert(node->left, v);    
            }

            calculate_height(node);
            return rebalance(node);
        }

        static TNode* remove(TNode* node, const T& v) {
            if(node == nullptr) {
                return nullptr;
            }

            if(v > node->value) {
                node->right = remove(node->right, v);
            } else if (v < node->value) {
                node->left = remove(node->left, v);
            } else {
                TNode* l = node->left;
                TNode* r = node->right;
                delete node;

                if(r == nullptr) {
                    return l;
                }
 
                TNode* m = find_min(r);
                m->right = remove_min(r);
                m->left = l;
                update_height(m);
                return rebalance(m);
            }
            calculate_height(node);
            return rebalance(node);
        }

        static void clear(TNode* node) {
            if(node == nullptr) {
                return;
            }
            clear(node->left);
            clear(node->right);
            delete node;
        }
};

class TDictionary : public TAVLTree<TKeyValue> {
    public:
        void Save(const std::string& fname) {
            std::ofstream out(fname, std::ios::binary | std::ios::out);
            if(out.bad() || out.fail()) {
                std::cout << "ERROR: Output file bad\n";
                return;
            }

            if(root == nullptr) {
                return;
            }

            TQueue<TNode*> q;
            q.Push(root);

            while(!q.IsEmpty()) {
                TNode* x = q.Pop();
                    
                out.write(x->value.key.c_str(), x->value.key.size() + 1);
                out.write(reinterpret_cast<const char *>(&x->value.value), sizeof(uint64_t));

                if(x->left) {
                    q.Push(x->left);
                }
                if(x->right) {
                    q.Push(x->right);
                }
            }
            out.close();
        }

        void Load(const std::string& fname) {
            std::ifstream in(fname, std::ios::binary | std::ios::in);
            if(in.bad() || in.fail()) {
                std::cout << "ERROR: Input file bad\n";
                return;
            }

            Clear();

            while(in.peek() != EOF) {
                uint64_t v;
                std::string k;

                char ch;
                while ((ch = in.get()) != '\0') {
                    k += ch;
                }
                in.read(reinterpret_cast<char *>(&v), sizeof(v));
                Insert(TKeyValue(k, v));
            }
            in.close();
        }
};

void MakeLower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
    [](unsigned char c){ return std::tolower(c); });
}

int main(void) {
    std::string cmd;
    TDictionary dict;

    while(std::cin >> cmd) {
        if(cmd == "+") {
            try {
                uint64_t v;
                std::cin >> cmd >> v;

                MakeLower(cmd);
                if(dict.Insert(TKeyValue(cmd, v))) {
                    std::cout << "OK\n";
                }
                else {
                    std::cout << "Exist\n";
                }
            } catch(std::bad_alloc const&) {
                std::cout << "ERROR: bad alloc\n";
            }
        }
        else if(cmd == "-") {
            std::cin >> cmd;

            MakeLower(cmd);
            if(dict.Remove({cmd, 0})) {
                std::cout << "OK\n";
            }
            else {
                std::cout << "NoSuchWord\n";
            }
        }
        else if(cmd == "!") {
            std::cin >> cmd;
            if(cmd == "Save") {
                std::cin >> cmd;
                dict.Save(cmd);
            }
            else {
                std::cin >> cmd;
                dict.Load(cmd);
            }
            std::cout << "OK\n";
        }
        else {
            try {
                MakeLower(cmd);
                uint64_t v = dict.TryFind({cmd, 0}).value;
                std::cout << "OK: " << v << '\n';
            }
            catch(std::runtime_error const&) {
                std::cout << "NoSuchWord\n";
            }
        }
    }
    
    return EXIT_SUCCESS;
}