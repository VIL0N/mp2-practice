#include <iostream>
#ifndef STACK_H
#define STACK_H
template <typename T>
class stack {
	size_t size;
	T* pMem;
	int top_ind;
public:
	stack(size_t sz) {
		if (sz == 0) throw std::exception ("out of range");
		size = sz;
		pMem = new T[size];
		top_ind = -1;
	}
	stack(size_t sz, T* elems, size_t num_elem) {
		if (sz == 0|| num_elem >sz||num_elem == 0) throw std::exception("out of range");
		size = sz;
		pMem = new T[size];
		for (int i = 0; i < num_elem; i++) {
			pMem[i] = elems[i];
		}
		top_ind = num_elem-1;
	}
	~stack() {
		delete[] pMem;
	}
	stack(const stack<T>&st) {
		size = st.size;
		top_ind = st.top_ind;
		pMem = new T[st.size];
		for (int i = 0; i <= top_ind; i++) {
			pMem[i] = st.pMem[i];
		}
	}
	stack(stack<T>&& st) {
		size = st.size;
		top_ind = st.top_ind;
		pMem = st.pMem;
		st.pMem = nullptr;
		st.size = 0;
		st.top_ind = -1;
	}

	T top() const {
		if (isEmpty() == 1) throw std::exception("out of range");
		return pMem[top_ind];
	}

	void push(T& elem) {
		if (isFull() == 1) throw std::exception("out of range");
		pMem[++top_ind] = elem;
	}
	void pop() {
		if (isEmpty() == 1) throw std::exception("out of range");
		top_ind--;
	}

	bool isFull() const {
		return top_ind == size - 1;
	}
	bool isEmpty() const {
		return top_ind == -1;
	}

	const stack<T> operator = (const stack<T>& st) {
		size = st.size;
		top_ind = st.top_ind;
		pMem = new T[size];
		for (int i = 0; i <= top_ind; i++) {
			pMem[i] = st[i];
		}
		return *this;
	}

	stack<T> operator = (stack<T>&& st) {
		size = st.size;
		top_ind = st.top_ind;
		pMem = st.pMem;
		st.pMem = nullptr;
		st.size = 0;
		st.top_ind = -1;
	}

	size_t stract_size() {
		return size;
	}
	bool operator == (const stack<T>& st) {
		if (this == &st) return 1;
		if (size != st.size) return 0;
		for (int i = 0; i < size; i++) {
			if (pMem[i] != st.pMem[i]) return 0;
		}
		return 1;
	}
	friend std::istream& operator>>(std::istream& istr, stack<T>& st) {
		int n;
		istr >> n;
		for (int i = 0; i <= st.top_ind;i++) {
			istr >> st.pMem[i];
		}
		st.top_ind = n;
		return istr;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const stack<T>& st) {
		ostr << st.top_ind;
		for (int i = 0; i <= st.top_ind;i++) {
			ostr << st.pMem[i] ;
		}
		return ostr;
	}
};


#endif // STACK_H
