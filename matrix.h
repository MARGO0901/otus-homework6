#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

struct VectorHash {
    size_t operator()(const std::vector<size_t> &v) const {
        size_t seed = v.size();
        for (auto i : v) {
        seed ^=
            std::hash<size_t>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

template<typename T, T V>
class Matrix {
public:
    Matrix(size_t dim) : dimension_(dim){}

    class Proxy {
        public:
            Proxy(Matrix &m, std::vector<size_t> ind) : matrix(m), index(std::move(ind)) {}

            Proxy operator[](size_t val) {
                std::vector<size_t> new_index = index;
                new_index.push_back(val);
                return Proxy(matrix, new_index);
            }

            //каноническое присваивание
            Proxy& operator=(const T& val) {
                matrix.value_[index] = val;
                return *this;
            }

            Proxy& operator=(const Proxy& other) {
                matrix.value_[index] = other.matrix.value_[other.index];
                return *this;
            }

        private:
            Matrix &matrix;
            std::vector<std::size_t> index;
    };

    Proxy operator[](std::size_t index) {
        return Proxy(*this, {index});
    }

    size_t size() const { 
        int count = 0;
        for (const auto &[key, val] : value_) {
          if (val != V)
            count++;
        }
        return count;
    }

    void print() {
        for (const auto &[key, value] : value_) {
            if (value != V) {
                std::cout << "[";
                for (size_t i = 0; i < key.size(); i++) {
                    std::cout << key[i];
                    if (i < (key.size() - 1))
                        std::cout << "][";
                }
                std::cout << "] = "  << value << std::endl;
            }
        }
    }

    void printElement(const std::vector<std::size_t> &index) {
        auto it = value_.find(index);
        T val = (it != value_.end()) ? it->second : V;
        std::cout << val;
    }

private:
    std::unordered_map<std::vector<std::size_t>, T, VectorHash> value_;
    std::size_t dimension_ = 2;
};

