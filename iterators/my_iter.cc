// Implementing my own iterator over a wrapper of a std::vector.
#include <vector>
#include <iostream>
#include <iterator>

template <typename T>
class Vec
{
public:
    explicit Vec(const std::vector<T> &values) : values_(values) {}
    explicit Vec(std::vector<T> &&values) : values_(std::move(values)) {}

    class iter : public std::iterator<std::input_iterator_tag, T>
    {
    public:
        iter(Vec<T> &vec, int idx) : vec_(vec), idx_(idx) {}
        bool operator==(iter other) const { return idx_ == other.idx_; }
        bool operator!=(iter other) const { return idx_ != other.idx_; }
        iter &operator++()
        {
            ++idx_;
            return *this;
        }
        iter operator++(int)
        {
            iter result = *this;
            ++idx_;
            return result;
        }
        T &operator*() { return vec_[idx_]; }

    private:
        Vec<T>& vec_;
        int idx_;
    };

    T& operator[](size_t idx) {
        return values_[idx];
    }

    iter begin()
    {
        return iter(*this, 0);
    }
    iter end()
    {
        return iter(*this, values_.size());
    }

private:
    std::vector<T> values_;
};

// template <typename T>
// typename Vec<T>::iter begin(const Vec<T> &v) { return Vec<T>::iter(0); }

// template <typename T>
// typename Vec<T>::iter end(const Vec<T> &v) { return Vec<T>::iter(v.size()); }

int main()
{
    auto xs = Vec<int>({1, 2, 3});
    auto it = std::find_if(xs.begin(), xs.end(), [](int x) { return x == 2; });
    if (it != xs.end()) {
        std::cout << "Found element: " << *it << "\n";
        *it = -*it;
    }
    for (auto x : xs)
    {
        std::cout << x << "\n";
    }
    return 0;
}