#pragma once

#include <algorithm>
#include <utility>
#include <limits>
#include <memory>
#include <vector>

namespace util {

template <
    typename Key,
    typename T,
    typename Compare = std::less<Key>,
    typename Allocator = std::allocator<std::pair<Key, T> >
>
class assoc_array {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<const Key, T> value_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename std::vector<std::pair<Key, T>, Allocator>::iterator iterator;
    typedef typename std::vector<std::pair<Key, T>, Allocator>::const_iterator const_iterator;

    iterator begin() {
        return m_vector.begin();
    }

    iterator end() {
        return m_vector.end();
    }

    const_iterator begin() const {
        return m_vector.begin();
    }

    const_iterator end() const {
        return m_vector.end();
    }

    const_iterator cbegin() const {
        return m_vector.begin();
    }

    const_iterator cend() const {
        return m_vector.end();
    }

    void clear() {
        m_vector.clear();
    }

    size_type count(const key_type& key) const {
        auto it = find(key);
        if (it != end()) {
            return 1;
        }

        return 0;
    }

    bool empty() const {
        return m_vector.empty();
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    size_type size() const {
        return m_vector.size();
    }

    const_iterator find(const key_type& key) const {
        const_iterator it = std::lower_bound(
                m_vector.begin(),
                m_vector.end(),
                key,
                [](const value_type& v, const key_type& key) -> bool { return Compare()(v.first, key); });

        if (it == m_vector.end() || it->first != key) {
            return m_vector.end();
        }

        return it;
    }

    iterator find(const key_type& key) {
        iterator it = std::lower_bound(
                m_vector.begin(),
                m_vector.end(),
                key,
                [](const value_type& v, const key_type& key) -> bool { return Compare()(v.first, key); });

        if (it == m_vector.end() || it->first != key) {
            return m_vector.end();
        }

        return it;
    }

    iterator erase(iterator it) {
        return m_vector.erase(it);
    }

    size_type erase(const key_type& key) {
        iterator it = find(key);
        if (it != end()) {
            erase(it);
            return 1;
        }

        return 0;
    }

    std::pair<iterator, bool> insert(const value_type& value) {
        iterator it = std::lower_bound(
                m_vector.begin(),
                m_vector.end(),
                value,
                [](const value_type& left, const value_type& right) -> bool { return Compare()(left.first, right.first); });

        if (it == m_vector.end() || it->first != value.first) {
            it = m_vector.insert(it, value);
            return std::pair<iterator, bool>(it, true);
        }

        return std::pair<iterator, bool>(it, false);
    }

    T& operator[](const key_type& key) {
        iterator it = std::lower_bound(
                m_vector.begin(),
                m_vector.end(),
                key,
                [](const value_type& v, const key_type& key) -> bool { return Compare()(v.first, key); });

        // No value with this key, create a default one
        if (it == m_vector.end() || it->first != key) {
            it = m_vector.insert(it, std::pair<Key, T>(key, T()));
        }

        return it->second;
    }

    const T& operator[](const key_type& key) const {
        const_iterator it = std::lower_bound(
                m_vector.begin(),
                m_vector.end(),
                key,
                [](const value_type& v, const key_type& key) -> bool { return Compare()(v.first, key); });

        // No value with this key, create a default one
        if (it == m_vector.end() || it->first != it) {
            it = m_vector.insert(it, std::pair<Key, T>(key, T()));
        }

        return it->second;
    }

    void swap(assoc_array& other) {
        m_vector.swap(other.m_vector);
    }

private:
    std::vector<std::pair<Key, T>, Allocator> m_vector;
};

} // namespace util
