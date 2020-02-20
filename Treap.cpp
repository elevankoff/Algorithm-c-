
int gen() {
    return rand()%100000007;
}

struct Treap {
    struct Node {
        int size, max, val, p;
        Node *l, *r;
        Node() : size(0), val(0), p(0), l(nullptr), r(nullptr) {};
        Node(int val) : val(val), size(1), p(gen()), l(nullptr), r(nullptr) {};
    };

    typedef Node* itNode;

    int size(itNode v) {
        return v ? v -> size : 0;
    }

    void update_size(itNode &v) {
        if (v) {
            v -> size = size(v -> l) + size(v -> r) + 1;
        }
    }

    void combine(itNode &v, itNode l, itNode r) {
        if (!l) {
            v = r;
            return;
        }
        if (!r) {
            v = l;
            return;
        }
    }

    void operation(itNode &v) {
        if (!v) return;
        combine(v, v -> l, v);
        combine(v, v, v -> r);
    }

    void merge(itNode &t, itNode l, itNode r) {
        if (!l) {
            t = r;
            return;
        }
        if (!r) {
            t = l;
            return;
        }
        if (l -> p > r -> p) merge(l -> r, l -> r, r), t = l;
            else {
                merge(r -> l, l, r -> l);
                t = r;
            }
        update_size(t);
        operation(t);
    }

    void split(itNode t, itNode &l, itNode &r, int k, int add = 0) {
        if (!t) {
            l = nullptr;
            r = nullptr;
            return;
        }
        int index = add + size(t -> l);
        if (index <= k) {
            split(t -> r, t -> r, r, k, index + 1);
            l = t;
        } else {
            split(t -> l, l, t -> l, k, add);
            r = t;
        }
        update_size(t);
        operation(t);
    }

    itNode root;
    Treap() {
        root = nullptr;
    }

    void insert(int pos, int val) {
        if (!root) {
            itNode New = new Node(val);
            root = New;
            return;
        }
        itNode l, r, New = new Node(val);
        split(root, l, r, pos - 1);
        merge(l, l, New);
        merge(root, l, r);
    }

    void move(int pos) {
        itNode l, r, x;
        split(root, l, r, pos - 1);
        split(r, x, r, 0);
        std::cout << x->val + 1 << " ";
        merge(root, x, l);
        merge(root, root, r);
    }
};

