#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);
std::uniform_int_distribution<> dis(1, 10000);

class Container {
    private:
    std::vector<bool> state;
    std::vector<int> size, nodes;
    int order;
    inline int p(int x, int y, int z) {
        return (x-1)*order*order + (y-1)*order + z;
    }

    public:
    Container(int s, double x = 100):order(s) {
        int pr = x * 100;
        nodes.push_back(0);
        size.push_back(1);
        state.push_back(true);
        for(int i = 1; i <= s * s * s; i++) {
            int j = dis(gen);
            state.push_back((j <= pr));
            size.push_back(1);
            nodes.push_back(i);
        }
        nodes.push_back(s*s*s+1);
        size.push_back(1);
        state.push_back(true);

        for(int j = 1; j <= order; j++) {
            for(int k = 1; k <= order; k++) {
                if(state[p(1, j, k)]) {unite(p(1, j, k), 0);}
                if(state[p(order, j, k)]) {unite(p(order, j, k), order*order*order+1);}
            }
        }
        form();
    }
    
    void form() {
        int i, j, k;
        for(i = 1; i <= order; i++) {
            for(j = 1; j <= order; j++) {
                for(k = 1; k <= order; k++) {
                    if(state[p(i, j, k)]) {connect(i, j, k);}
                }
            }
        }
    }
    int root(int x) {
        while(nodes[x] != x) {
            x = nodes[x];
        }
        return x;
    }
    void unite(int a, int b) {
        if(connected(a, b)) {
            return;
        }
        int root_a = root(a), root_b = root(b);
        if(size[root_a] > size[root_b]) {
            nodes[root_b] = root_a;
            size[root_a] += size[root_b];
        }
        else {
            nodes[root_a] = root_b;
            size[root_b] += size[root_a];
        }
    }
    bool connected(int a, int b) {
        return (root(a) == root(b));
    }
    bool percolating() {
        return connected(0, order*order*order+1);
    }
    void connect(int x, int y, int z) {
        if(x == 1) {
            if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
            if(y == 1) {
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(y == order) {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(z == 1) {
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(z == order) {
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
            }
        }
        else if(x == order) {
            if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
            if(y == 1) {
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(y == order) {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(z == 1) {
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(z == order) {
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
            }
        }
        else if(y == 1) {
            if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
            if(x == 1) {
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }    
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(x == order) {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }    
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(z == 1) {
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else if(z == order) {
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
            }
        }
        else if(y == order) {
            if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
            if(x == 1) {
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }    
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(x == order) {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(z == 1) {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                }
                else if(z == order) {
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }    
                else {
                    if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                    if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                }
            }
            else if(z == 1) {
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else if(z == order) {
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
                if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
            }
        }
        else if(z == 0) {
            if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
            if(x == 1) {
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(x == order) {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(y == 0) {
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else  {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else if(y == order) {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else  {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
            }
        }
        else if(z == order) {
            if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
            if(x == 1) {
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(x == order) {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(y == 1) {
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
                else if(y == order) {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                }
                else {
                    if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                    if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                }
            }
            else if(y == 0) {
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else  {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else if(y == order) {
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(x == 1) {
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
                else if(x == order) {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                }
                else  {
                    if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                    if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                }
            }
            else {
                if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
                if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
                if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
                if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
                
            }
        }
        else {
            if(state[p(x-1, y, z)]) {unite(p(x-1, y, z), p(x, y, z));} //up
            if(state[p(x+1, y, z)]) {unite(p(x+1, y, z), p(x, y, z));} //down
            if(state[p(x, y-1, z)]) {unite(p(x, y-1, z), p(x, y, z));} //north
            if(state[p(x, y+1, z)]) {unite(p(x, y+1, z), p(x, y, z));} //south
            if(state[p(x, y, z+1)]) {unite(p(x, y, z+1), p(x, y, z));} //east
            if(state[p(x, y, z-1)]) {unite(p(x, y, z-1), p(x, y, z));} //west
        }
    }
    void display() {
        for(int i = 1; i <= order; i++) {
            for(int j = 1; j <= order; j++) {
                for(int k = 1; k <= order; k++) {
                    std::cout << state[p(i, j, k)] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
    void info() {
        for(int i = 1; i <= order; i++) {
            for(int j = 1; j <= order; j++) {
                for(int k = 1; k <= order; k++) {
                    std::cout << root(p(i, j, k)) << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "In: " << root(0) << "  Out: " << root(order*order*order+1) << "\n";
    }

};

int main() {
    double start = 0, end = 100, per, mid;
    int iter, c, times;
    Container *exp;
    std::cout << "Enter the times to iterate: ";
    std::cin >> iter;
    std::cout << "Times to perform calculation: ";
    std::cin >> times;
    for(int i = 0; i < iter; i++) {
        mid = (start+end) / 2;
        c = 0;
        for(int j = 0; j < times; j++) {
            exp = new Container(100, mid);
            if(exp->percolating()) {c++;}
            delete exp;
        }
        per = (static_cast<double>(c) / times) * 100;
        if(per > 50.0) {
            end = mid;
        }
        else {
            start = mid;
        }
    }
    std::cout << "Result: " << std::fixed << std::setprecision(6) << mid/100;
    return 0;
}