//  Copyright 2025 Guseva Olga

#pragma once

#include <iostream>
#include <cmath>
#include <random>
#define STEP_OF_CAPACITY 15

enum State { empty, busy, deleted };

template <class T> class TVector;
template <class T> void hoara_sort(TVector<T>& data);
template <class T>
void hoara_sort_rec(TVector<T>& data, size_t left, size_t right);
template <class T>
int find_first_elem(const TVector<T>& data, T value) noexcept;
template <class T>
int find_last_elem(const TVector<T>& data, T value) noexcept;
template <class T>
int* find_elem(const TVector<T>& data, T value) noexcept;
template <class T>
T* find_first_elem_by_pointer(const TVector<T>& data, T value) noexcept;
template <class T>
T* find_last_elem_by_pointer(const TVector<T>& data, T value) noexcept;
template <class T>
TVector<T*> find_elem_by_pointer(const TVector<T>& data, T value) noexcept;
template <class T> void shuffle(TVector<T>& data);

template <class T>
class TVector {
    T* _data;
    size_t _capacity;
    size_t _size;
    size_t _deleted;
    State* _states;

public:
    explicit TVector(size_t size = 0);
    TVector(const size_t size, const T* data);
    TVector(const TVector<T>& other);
    TVector(const size_t size, const std::initializer_list<T> data);
    ~TVector();

    bool operator == (const TVector<T>& other) const noexcept;
    bool operator != (const TVector<T>& other) const noexcept;
    TVector<T>& operator = (const TVector<T>& other);
    T& operator[] (size_t index);
    const T& operator[](size_t index) const;

    const T& at(size_t index) const;

    inline bool is_empty() const noexcept;

    inline const T* data() const noexcept;
    inline const size_t size() const noexcept;
    inline const size_t capacity() const noexcept;
    inline const size_t deleted() const noexcept;
    inline const State* states() const noexcept;

    inline const T& front() const;
    inline const T& back() const;
    inline const T* begin() const noexcept;
    inline const T* end() const noexcept;

    void shrink_to_fit() noexcept;
    void resize(size_t new_size) noexcept;
    void reserve(size_t new_capacity) noexcept;
    void clear() noexcept;

    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    void insert(const size_t index, const T& value);
    void insert(const size_t index, size_t count, const T& value);
    void insert(const size_t index, std::initializer_list<T> data);

    void pop_back();
    void pop_front();
    void erase(size_t index);

    void assign(size_t count, const T& value) noexcept;
    void assign(std::initializer_list<T> data) noexcept;
    void replace(const T& value, const T& new_value) noexcept;

    void print() noexcept;
    void print_all_info() noexcept;

    friend void hoara_sort_rec<T>(TVector<T>& data, size_t left, size_t right);
    friend void hoara_sort<T>(TVector<T>& data);
    friend int find_first_elem<T>(const TVector<T>& data, T value) noexcept;
    friend int find_last_elem<T>(const TVector<T>& data, T value) noexcept;
    friend int* find_elem<T>(const TVector<T>& data, T value) noexcept;
    friend T* find_first_elem_by_pointer<T>(const TVector<T>& data,
        T value) noexcept;
    friend T* find_last_elem_by_pointer<T>(const TVector<T>& data,
        T value) noexcept;
    friend TVector<T*> find_elem_by_pointer<T>(const TVector<T>& data,
        T value) noexcept;
    friend void shuffle<T>(TVector<T>& data);
    /* ... */
private:
    /* ... */
    inline bool is_full() const noexcept;
    void make_space_for_insert(size_t index, size_t count);
    int calculate_real_index(size_t index) const noexcept;
    T* calculate_real_address(size_t index) const noexcept;
    void resize_for_insert(size_t new_size) noexcept;
    size_t rand_generation(size_t min, size_t max) const noexcept;
};

template <class T>
TVector<T>::TVector(size_t size) {
    _size = size;
    _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < size; i++) {
        //_data[i] = T();
        _states[i] = State::busy;
    }
    for (size_t i = size; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <class T>
TVector<T>::TVector(size_t size, const T* data) {
    _size = size;
    _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < size; i++) {
        _data[i] = data[i];
        _states[i] = State::busy;
    }
    for (size_t i = size; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <class T>
TVector<T>::TVector(const TVector<T>& other) {
    if (&other == NULL)
        throw std::logic_error("The object not found\n");

    _size = other._size;
    _capacity = other._capacity;
    _deleted = other._deleted;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }
}

template <class T>
TVector<T>::TVector(size_t size, std::initializer_list<T> data) {
    _size = size;
    _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    auto it = data.begin();
    size_t i = 0;
    for (; it != data.end() && i < size; i++, it++) {
        _data[i] = *it;
        _states[i] = State::busy;
    }
    for (; i < _size; i++) {
        //_data[i] = T();
        _states[i] = State::busy;
    }
    for (; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <class T>
TVector<T>::~TVector() {
    delete[] _data;
    _data = nullptr;

    delete[] _states;
    _states = nullptr;
}

template <class T>
TVector<T>& TVector<T>::operator = (const TVector& other) {
    if (&other == NULL) {
        throw std::logic_error("The object is empty ");
    }
    if (this == &other) {
        return *this;
    }
    _size = other._size;
    _capacity = other._capacity;
    _deleted = other._deleted;

    delete[] _data;
    delete[] _states;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = other._data[i];
        _states[i] = other._states[i];
    }

    return *this;
}

template <class T>
bool TVector<T>::operator == (const TVector<T>& other) const noexcept {
    if (_size - _deleted != other._size - other._deleted) {
        return false;
    }
    size_t i = 0, j = 0;

    while (i < _capacity && j < other._capacity) {
        while (i < _capacity && _states[i] != State::busy)
            i++;
        while (j < other._capacity && other._states[j] != State::busy)
            j++;
        if (_data[i++] != other._data[j++]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool TVector<T>::operator != (const TVector<T>& other) const noexcept {
    return !((*this) == other);
}

template <class T>
T& TVector<T>::operator[](size_t index) {
    size_t real_index = calculate_real_index(index);
    return _data[real_index];
}

template <class T>
const T& TVector<T>::operator[](size_t index) const {
    size_t real_index = calculate_real_index(index);
    return _data[real_index];
}

template <class T>
const T& TVector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::invalid_argument("Index is larger than vector size\n");
    }
    size_t new_index = calculate_real_index(index);
    if (new_index != -1) {
        return _data[new_index];
    }
    else {
        throw std::logic_error("Index is not found\n");
    }
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {
    if (_size - _deleted == 0) return true;
    return false;
    /*
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == State::busy)
            return false;
    }
    return true;
    */
}

template <class T>
inline bool TVector<T>::is_full() const noexcept {
    if (_deleted == 0 && _size == _capacity) return true;
    return false;
    /*
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == State::empty || _states[i] == State::deleted)
            return false;
    }
    return true;
    */
}

template <class T>
inline const T* TVector<T>::data() const noexcept {
    if (is_empty()) return nullptr;
    T* new_address = calculate_real_address(0);
    return new_address;
}

template <class T>
inline const size_t TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
inline const size_t TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <class T>
inline const size_t TVector<T>::deleted() const noexcept {
    return _deleted;
}

template <class T>
inline const State* TVector<T>::states() const noexcept {
    return _states;
}

template <class T>
inline const T& TVector<T>::front() const {
    if (is_empty())
        throw std::invalid_argument("Empty vector\n");
    /*
    if (calculate_real_index(0) == -1) {
        throw std::logic_error("Index not found\n");
    }
    */
    return _data[calculate_real_index(0)];
}

template <class T>
inline const T& TVector<T>::back() const {
    if (is_empty())
        throw std::invalid_argument("Empty vector\n");
    /*
    if (calculate_real_index(_size - 1) == -1) {
        throw std::logic_error("Index not found\n");
    }
    */
    return _data[_size - 1];
}

template <class T>
inline const T* TVector<T>::begin() const noexcept {
    if (is_empty()) return nullptr;
    T* new_address = calculate_real_address(0);
    return new_address;
}

template <class T>
inline const T* TVector<T>::end() const noexcept {
    if (is_empty()) return nullptr;
    T* new_address = calculate_real_address(_size - 1) + 1;
    return new_address;
}

template <class T>
void TVector<T>::shrink_to_fit() noexcept {
    if (_deleted == 0 && _size == _capacity) {
        return;
    }
    size_t new_capacity = _size - _deleted;
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    size_t j = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == State::busy) {
            if (j == new_capacity) break;
            new_data[j] = _data[i];
            new_states[j] = State::busy;
            j++;
        }
    }
    for (size_t i = j; i < new_capacity; i++) {
        new_states[i] = State::empty;
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_capacity;
}

template <class T>
void TVector<T>::assign(size_t count, const T& value) noexcept {
    if (count == _size) {
        for (size_t i = 0; i < _size; i++) {
            _data[i] = value;
            _states[i] = State::busy;
        }
        return;
    }

    T* new_data; State* new_states;
    size_t new_size = count;
    size_t new_capacity = (new_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

    if (new_size == 0) {
        clear();
        return;
    }
    else {
        new_data = new T[new_capacity];
        new_states = new State[new_capacity];

        for (size_t i = 0; i < new_size; i++) {
            new_data[i] = value;
            new_states[i] = State::busy;
        }
        for (size_t i = new_size; i < new_capacity; i++) {
            new_states[i] = State::empty;
        }
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
}

template <class T>
void TVector<T>::assign(std::initializer_list<T> data) noexcept {
    size_t new_size = data.size();

    if (new_size == _size) {
        auto it = data.begin();
        for (size_t i = 0; it != data.end(); i++, it++) {
            _data[i] = *it;
            _states[i] = State::busy;
        }
        return;
    }

    T* new_data; State* new_states;
    size_t new_capacity = (new_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

    if (new_size == 0) {
        clear();
        return;
    }
    else {
        new_data = new T[new_capacity];
        new_states = new State[new_capacity];

        size_t i = 0;
        auto it = data.begin();
        for (; it != data.end(); i++, it++) {
            new_data[i] = *it;
            new_states[i] = State::busy;
        }
        for (; i < new_capacity; i++) {
            new_states[i] = State::empty;
        }
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
}

template <class T>
void TVector<T>::replace(const T& value, const T& new_value) noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] == State::busy)
            _data[i] = new_value;
    }
}

template <class T>
void TVector<T>::clear() noexcept {
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }

    if (_states != nullptr) {
        delete[] _states;
        _states = nullptr;
    }

    _data = nullptr;
    _states = nullptr;
    _capacity = 0;
    _deleted = 0;
    _size = 0;
}

template <class T>
void TVector<T>::resize(size_t new_size) noexcept {
    if (new_size == _size) return;

    T* new_data; State* new_states;
    size_t new_capacity = (new_size / STEP_OF_CAPACITY + 1)
        * STEP_OF_CAPACITY;
    size_t lowest_capacity = new_capacity > _capacity ?
        _capacity : new_capacity;

    if (new_size == 0) {
        clear();
        return;
    }
    else {
        new_data = new T[new_capacity];
        new_states = new State[new_capacity];

        size_t busy_count = 0;
        if (_data != nullptr) {
            for (size_t i = 0; i < lowest_capacity; i++) {
                if (_states[i] == State::busy) {
                    if (busy_count < new_size) {
                        new_data[busy_count] = _data[i];
                        new_states[busy_count] = _states[i];
                        busy_count++;
                    }
                }
            }
        }
        for (size_t i = busy_count; i < new_size; i++) {
            new_data[i] = T();
            new_states[i] = State::busy;
        }
        for (size_t i = new_size; i < new_capacity; i++) {
            new_states[i] = State::empty;
        }
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
}

template <class T>
void TVector<T>::resize_for_insert(size_t new_size) noexcept {
    T* new_data; State* new_states;
    size_t new_capacity = (new_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;

    new_data = new T[new_capacity];
    new_states = new State[new_capacity];

    size_t busy_count = 0;
    if (_data != nullptr) {
        for (size_t i = 0; i < _capacity; i++) {
            if (_states[i] == State::busy) {
                if (busy_count < new_size) {
                    new_data[busy_count] = _data[i];
                    new_states[busy_count] = _states[i];
                    busy_count++;
                }
            }
        }
    }
    for (size_t i = busy_count; i < new_size; i++) {
        new_states[i] = State::empty;
    }
    for (size_t i = new_size; i < new_capacity; i++) {
        new_states[i] = State::empty;
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
}

template <class T>
void TVector<T>::reserve(size_t new_capacity) noexcept {
    if (new_capacity <= _capacity) return;

    size_t new_size = _size;
    T* new_data; State* new_states;

    new_data = new T[new_capacity];
    new_states = new State[new_capacity];

    if (_data != nullptr) {
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
            new_states[i] = _states[i];
        }
    }
    for (size_t i = _size; i < new_capacity; i++) {
        new_states[i] = State::empty;
    }

    clear();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
}

/*
template <class T>
void TVector<T>::make_space_for_insert(size_t index, size_t count) {
    size_t deleted_after_index = 0;
    for (size_t i = index; i < _size; i++) {
        if (_states[i] == State::deleted) deleted_after_index++;
        if (_states[i] == State::empty) break;
    }

    int j = count - deleted_after_index;
    for (size_t i = _size + j - 1; i > index; i--) {
        while (_states[i - j] == State::deleted) j++;

        if (j > 0 && i < _capacity) {
            _data[i] = _data[i - j];
            _states[i] = _states[i - j];
        }
    }

    size_t new_deleted = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] == State::deleted) new_deleted++;
        if (_states[i] == State::empty) break;
    }
    _size -= _deleted - new_deleted;
    _deleted = new_deleted;
}
*/

template <class T>
void TVector<T>::make_space_for_insert(size_t index, size_t count) {
    for (size_t i = _size + count - 1; i > index; i--) {
        if (i < _capacity && i - count >= 0) {
            _data[i] = _data[i - count];
            _states[i] = _states[i - count];
        }
    }
}

template <class T>
int TVector<T>::calculate_real_index(size_t index) const noexcept {
    if (_deleted == 0) return index;

    size_t busy_count = 0;
    size_t real_index = 0;

    for (; real_index < _size; real_index++) {
        if (busy_count == index) {
            while (_states[real_index] != State::busy && real_index < _size)
                real_index++;
            if (_states[real_index] == State::busy)
                return real_index;
        }
        if (_states[real_index] == State::busy) busy_count++;
    }
    if (busy_count == index && real_index == _size) return real_index;
    return -1;
}

template <class T>
T* TVector<T>::calculate_real_address(size_t index) const noexcept {
    size_t busy_count = 0;
    for (size_t real_index = 0; real_index < _size; real_index++) {
        if (busy_count == index) return &_data[real_index];
        if (_states[real_index] == State::busy) busy_count++;
    }

    return nullptr;
}

template <class T>
void TVector<T>::push_front(const T& value) noexcept {
    size_t left_free = 0;

    if (_size == _capacity) {
        resize_for_insert(_size - _deleted + 1);
    }
    else {
        _size++;
    }

    if (_states[0] == State::busy) {
        make_space_for_insert(0, 1);
    }
    else {
        while (left_free < _size && _states[left_free + 1] == State::deleted)
            left_free++;
    }

    _data[left_free] = value;
    if (_states[left_free] == State::deleted) {
        _deleted--; _size--;
    }
    _states[left_free] = State::busy;

    if (is_full()) {
        reserve((_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY);
    }
}

template <class T>
void TVector<T>::push_back(const T& value) noexcept {
    size_t right_free = _size;

    if (_size == _capacity) {
        resize_for_insert(_size - _deleted + 1);
    }
    else {
        _size++;
    }

    while (right_free > 0 && _states[right_free - 1] != State::busy)
        right_free--;

    _data[right_free] = value;
    if (_states[right_free] == State::deleted) {
        _deleted--; _size--;
    }
    _states[right_free] = State::busy;

    if (is_full()) {
        reserve((_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY);
    }
}

template <class T>
void TVector<T>::insert(const size_t index, const T& value) {
    if (index > _size)
        throw std::invalid_argument("Index is larger than vector size\n");

    if (_size == _capacity) {
        resize_for_insert(_size - _deleted + 1);
        make_space_for_insert(index, 1);
    }
    else {
        make_space_for_insert(calculate_real_index(index), 1);
        _size++;
    }

    size_t real_index = calculate_real_index(index);

    _data[real_index] = value;
    if (_states[real_index] == State::deleted) {
        _deleted--; _size--;
    }
    _states[real_index] = State::busy;

    if (is_full()) {
        reserve((_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY);
    }
}

template <class T>
void TVector<T>::insert(const size_t index, size_t count, const T& value) {
    if (index > _size)
        throw std::invalid_argument("Index is larger than vector size\n");

    if (_size + count > _capacity) {
        resize_for_insert(_size - _deleted + count);
        make_space_for_insert(index, count);
    }
    else {
        make_space_for_insert(calculate_real_index(index), count);
        _size += count;
    }

    size_t real_index = calculate_real_index(index);

    for (size_t i = 0; i < count; i++) {
        _data[real_index + i] = value;
        if (_states[real_index] == State::deleted) {
            _deleted--; _size--;
        }
        _states[real_index + i] = State::busy;
    }

    if (is_full()) {
        reserve((_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY);
    }
}


template <class T>
void TVector<T>::insert(const size_t index,
    std::initializer_list<T> data_list) {
    if (index > _size)
        throw std::invalid_argument("Index is larger than vector size\n");

    if (_size + data_list.size() > _capacity) {
        resize_for_insert(_size + data_list.size() - _deleted);
        make_space_for_insert(index, data_list.size());
    }
    else {
        make_space_for_insert(calculate_real_index(index), data_list.size());
        _size += data_list.size();
    }

    size_t real_index = calculate_real_index(index);

    auto it = data_list.begin();
    for (size_t i = 0; i < data_list.size(); i++) {
        _data[real_index + i] = *(it + i);
        if (_states[real_index] == State::deleted) {
            _deleted--; _size--;
        }
        _states[real_index + i] = State::busy;
    }

    if (is_full()) {
        reserve((_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY);
    }
}

template <class T>
void TVector<T>::pop_back() {
    if (is_empty())
        throw std::logic_error("Index is larger than vector size\n");

    int first_busy_index = -1;
    for (int i = _capacity; i >= 0; i--) {
        if (_states[i] == State::busy) {
            first_busy_index = i;
            break;
        }
    }

    if (first_busy_index != -1) {
        _states[first_busy_index] = State::empty;
        _deleted++;
    }

    if (_deleted >= _size * 0.2)
        resize(_size - _deleted);
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty())
        throw std::logic_error("Index is larger than vector size\n");

    int first_busy_index = -1;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == State::busy) {
            first_busy_index = i;
            break;
        }
    }

    if (first_busy_index != -1) {
        _states[first_busy_index] = State::deleted;
        _deleted++;
    }

    if (_deleted >= _size * 0.2)
        resize(_size - _deleted);
}

template <class T>
void TVector<T>::erase(size_t index) {
    bool is_last_elem = true;

    if (is_empty())
        throw std::logic_error("Index is larger than vector size\n");

    for (size_t i = index + 1; i < _size; i++) {
        if (_states[i] == State::busy) {
            is_last_elem = false;
            break;
        }
    }
    if (is_last_elem) {
        pop_back();
    }
    else {
        size_t real_index = calculate_real_index(index);

        while (_states[real_index] == State::deleted) real_index++;
        _states[real_index] = State::deleted;
        _deleted++;
    }

    if (_deleted >= _size * 0.2)
        resize(_size - _deleted);
}

template <class T>
void TVector<T>::print() noexcept {
    std::cout << "Your vector: ";

    for (int i = 0; i < _size; i++) {
        if (_states[i] == State::busy) {
            std::cout << _data[i] << " ";
        }
    }
    std::cout << std::endl;
}

template <class T>
void TVector<T>::print_all_info() noexcept {
    std::cout << "--------------------------------------------"
        << std::endl;
    std::cout << "CAPACITY: " << _capacity << std::endl;
    std::cout << "SIZE: " << _size << std::endl;
    std::cout << "DELETED: " << _deleted << std::endl;
    std::cout << "DATA: ";
    if (_data != nullptr) {
        for (int i = 0; i < _capacity; i++) {
            std::cout << _data[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "nullptr" << std::endl;
    }
    std::cout << "STATES: ";
    if (_states != nullptr) {
        for (int i = 0; i < _capacity; i++) {
            std::cout << _states[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "nullptr" << std::endl;
    }
    print();
    std::cout << "--------------------------------------------"
        << std::endl;
}

template <class T>
void hoara_sort(TVector<T>& data) {
    if (data._size < 2) return;
    hoara_sort_rec(data, 0, data._size - 1);
}

template <class T>
void hoara_sort_rec(TVector<T>& data, size_t left, size_t right) {
    if (left < right) {
        size_t base = (left + right) / 2;
        size_t l = left, r = right;
        const T base_value = data[base];
        while (l <= r) {
            while (data._data[l] < base_value) {
                l++;
            }
            while (data._data[r] > base_value) {
                r--;
            }
            if (l <= r) {
                T tmp = data._data[l];
                data._data[l] = data._data[r];
                data._data[r] = tmp;

                State tmp2 = data._states[l];
                data._states[l] = data._states[r];
                data._states[r] = tmp2;
                l++;
                if (r > 0) r--;
            }
            else {
                break;
            }
        }
        hoara_sort_rec(data, left, r);
        hoara_sort_rec(data, l, right);
    }
}

template<class T>
int find_first_elem(const TVector<T>& data, T value) noexcept {
    size_t count_not_busy = 0;
    for (size_t i = 0; i < data._size; i++) {
        if (data._states[i] != State::busy) count_not_busy++;

        if (data._data[i] == value && data._states[i] == State::busy)
            return i - count_not_busy;
    }
    return -1;
}

template <class T>
int find_last_elem(const TVector<T>& data, T value) noexcept {
    size_t count_not_busy = 0;
    int actual_index = -1;
    for (size_t i = 0; i < data._size; i++) {
        if (data._states[i] != State::busy) count_not_busy++;

        if (data._data[i] == value && data._states[i] == State::busy)
            actual_index = i - count_not_busy;
    }
    return actual_index;
}

template <class T>
int* find_elem(const TVector<T>& data, T value) noexcept {
    size_t occurrences_count = 0;
    for (size_t i = 0; i < data._size; i++) {
        if (data[i] == value) occurrences_count++;
    }

    int* result = new int[occurrences_count + 1];
    result[0] = occurrences_count;

    if (occurrences_count > 0) {
        size_t index = 1, not_busy_count = 0;

        for (size_t i = 0; i < data._size; i++) {
            if (data._states[i] != State::busy)
                not_busy_count++;
            if (data._data[i] == value && data._states[i] == State::busy)
                result[index++] = i - not_busy_count;
        }
    }
    return result;
}

template <class T>
T* find_first_elem_by_pointer(const TVector<T>& data, T value) noexcept {
    for (size_t i = 0; i < data._size; i++) {
        if (data._data[i] == value && data._states[i] == State::busy)
            return &data._data[i];
    }
    return nullptr;
}

template <class T>
T* find_last_elem_by_pointer(const TVector<T>& data, T value) noexcept {
    for (int i = data._size - 1; i >= 0; i--) {
        if (data._data[i] == value && data._states[i] == State::busy)
            return &data._data[i];
    }
    return nullptr;
}

template <class T>
TVector<T*> find_elem_by_pointer(const TVector<T>& data, T value) noexcept {
    size_t occurrences_count = 0;
    for (size_t i = 0; i < data._size; i++) {
        if (data[i] == value) occurrences_count++;
    }

    TVector<T*> result;
    if (occurrences_count > 0) {
        size_t index = 0, not_busy_count = 0;

        for (size_t i = 0; i < data._size; i++) {
            if (data._data[i] == value && data._states[i] == State::busy) {
                result.insert(index, &data._data[i]);
                index++;
            }
        }
    }
    return result;
}

template <class T>
size_t TVector<T>::rand_generation(size_t min, size_t max) const noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(gen);
}

template <class T>
void shuffle(TVector<T>& data) {
    if (data.size() == 0)
        throw std::invalid_argument("Size can't be zero\n");

    int i, rand_i;
    for (i = 0; i < data._size + data._deleted; i++) {
        rand_i = data.rand_generation(0, data._size + data._deleted - 1);

        T tmp = data._data[i];
        data._data[i] = data._data[rand_i];
        data._data[rand_i] = tmp;

        State tmp2 = data._states[i];
        data._states[i] = data._states[rand_i];
        data._states[rand_i] = tmp2;
    }
}
