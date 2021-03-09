#pragma once
#include <iostream>

template<typename T>
class DynamicArray
{
private:
	T*	arr;
	size_t phySize;
	size_t logSize;
public:
	DynamicArray(int size = 2) :logSize(), phySize(size), arr(new T[size]{}) {}
	DynamicArray(const DynamicArray& other):arr(nullptr),phySize(0),logSize(0){ *this = other; }
	~DynamicArray() {delete[](arr);}

	//Capacity
	size_t size()const			{ return logSize; }
	
	size_t capcity()const		{ return phySize; }
	
	bool empty()const			{ return !logSize; }
	
	void clear()				{ logSize = 0; }

	bool reserve(size_t _size) {
		if (_size <=phySize)
			return true;
		else {
			T* _newarray = new T[_size]{};

			for (size_t i = 0; i < logSize; ++i)
				_newarray[i] = arr[i];
			if (arr)
				delete[](arr);
			arr = _newarray;
			phySize = _size;

			return true;

		}
		return false;
		

	}

	bool resize() {
		++phySize *= 2;
		T* _newarray = new T[phySize]{};
		for (size_t i = 0; i < logSize; ++i)
			_newarray[i] = arr[i];
		if (arr)
			delete[](arr);
		arr = _newarray;

		return (arr);

	}

	bool resize(size_t size) {
		if (size < phySize) {
			logSize = size;
			return true;
		}
		if (reserve(size)) {
			logSize = size;
			return true;
		}
		return false;
	}

	void push_back(const T& val) {
		if (logSize == phySize)
			resize();
		arr[logSize++] = val;
	}

	const T front(){ return arr[0]; }

	const T& at(size_t _idx)const {
		if (_idx < 0 || _idx >= logSize)
			throw std::out_of_range("Invalid index!");
		return (*this)[_idx];
	}

	bool operator==(const DynamicArray& other)const {
		bool flag = (logSize == other.logSize && phySize == other.phySize);
		for (size_t i = 0; i < logSize && flag; ++i)
			flag = (arr[i] == other.arr[i]);

		return flag;
	}

	T& at(size_t _idx) {

		if (_idx < 0 || _idx >=logSize) 
			throw std::out_of_range("Invalid index!");

		return (*this)[_idx];
	}

	const T& operator[](size_t _idx)const {
		return arr[_idx]; }
	T& operator[](size_t _idx) { 
		return arr[_idx]; }

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			logSize = other.logSize;
			phySize = other.phySize;

			delete[](arr);
			arr = new T[phySize]{};
			for (size_t i = 0; i < logSize; ++i) {
				(*this)[i] = other[i];
			}
		}
		return *this;
	}



	class iterator {
	private:
		DynamicArray*	_darr;
		size_t			_idx;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using valu_type = T;
		using pointer = T*;
		using reference = T&;

		friend class const_iterator;
		friend class reverse_iterator;

		iterator(DynamicArray& arr, size_t idx) :_darr(&arr), _idx(idx){}
		iterator(const iterator& other):_darr(other._darr), _idx(other._idx){}


		const iterator& operator=(const iterator& other){
			_darr = other._darr;
			_idx = other._idx;
		}

		bool operator==(const iterator& other) {
			return(_darr == other._darr) && (_idx == other._idx);
		}

		bool operator!=(const iterator& other) {
			return !(*this == other);
		}

		T& operator*() { return _darr->arr[_idx]; }
		T* operator->() { return &_darr->arr[_idx]; }
	
		iterator& operator++() { ++_idx; return *this; }
		iterator& operator++(int) {
			iterator res(*this);
			++_idx;
			return res;
		}

		iterator& operator--() { --_idx; return *this; }
		iterator& operator--(int) {
			iterator res(*this);
			--_idx;
			return res;
		}


	};

	class reverse_iterator {
	private:
		DynamicArray* _darr;
		size_t			_idx;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using valu_type = T;
		using pointer = T*;
		using reference = T&;



		reverse_iterator(DynamicArray& arr, size_t idx) :_darr(&arr), _idx(idx) {}
		reverse_iterator(const iterator& other) :_darr(other._darr), _idx(other._idx) {}
		reverse_iterator(const reverse_iterator& other) :_darr(other._darr), _idx(other._idx) {}

		const reverse_iterator& operator=(const reverse_iterator& other) {
			_darr = other._darr;
			_idx = other._idx;
		}

		const reverse_iterator& operator=(const iterator& other) {
			_darr = other._darr;
			_idx = other._idx;
		}

		bool operator==(const reverse_iterator& other)const {
			return(_darr == other._darr) && (_idx == other._idx);
		}

		bool operator!=(const reverse_iterator& other)const {
			return !(*this == other);
		}

		bool operator==(const iterator& other)const {
			return(_darr == other._darr) && (_idx == other._idx);
		}

		bool operator!=(const iterator& other)const {
			return !(*this == other);
		}

		T& operator*() { return _darr->arr[_idx]; }
		T* operator->() { return &_darr->arr[_idx]; }

		reverse_iterator& operator++() { --_idx; return *this; }
		reverse_iterator& operator++(int) {
			reverse_iterator res(*this);
			--_idx;
			return res;
		}

		reverse_iterator& operator--() { ++_idx; return *this; }
		reverse_iterator& operator--(int) {
			reverse_iterator res(*this);
			++_idx;
			return res;
		}


	};

	class const_iterator {
	private:
		const DynamicArray* _darr;
		size_t _idx;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using valu_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(DynamicArray& darr, size_t idx):_darr(darr),_idx(idx){}
		const_iterator(const const_iterator& other):_darr(other._darr),_idx(other._idx){}
		const_iterator(const iterator& other):_darr(other._darr), _idx(other._idx) {}

		const const_iterator& operator=(const iterator& other) {
			_darr = other._darr;
			_idx = other._idx;
		}

		bool operator==(const iterator& other)const {
			return(_darr == other._darr) && (_idx == other._idx);
		}

		bool operator==(const const_iterator& other)const{
			return(_darr == other._darr) && (_idx == other._idx);
		}

		bool operator!=(const iterator& other)const{
			return !(*this == other);
		}

		bool operator!=(const const_iterator& other)const {
			return !(*this == other);
		}

		const T& operator*()const { return _darr->arr[_idx]; }
		const T* operator->()const { return &_darr->arr[_idx]; }

		const_iterator& operator++() { ++_idx; return *this; }
		const_iterator& operator++(int) {
			const_iterator res(*this);
			++_idx;
			return res;
		}

		const_iterator& operator--() { --_idx; return *this; }
		const_iterator& operator--(int) {
			const_iterator res(*this);
			--_idx;
			return res;
		}


	};

	iterator begin() { return iterator{ *this,0 }; }
	iterator end() {return iterator(*this, logSize); }
	const_iterator cbegin()const { return const_iterator(*this, 0); }
	const_iterator cend()const { return const_iterator(*this, logSize); }

};

