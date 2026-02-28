#include <iostream>
#include <initializer_list>

class MyVector {
	private: 
		int * data;
		size_t size;
		size_t capacity;
	public:
		MyVector() : data(nullptr), size(0), capacity(0) {
			std::cout << "Default constructor" << std::endl;
		};

		MyVector(size_t size) : MyVector(size, 0) {
                        std::cout << "Parameterized (one) constructor" << std::endl;
		}

		MyVector(size_t size, int val) : size{size}, capacity{size} {
			data = new int[size];
			for(int i = 0; i < size; ++i) {
				data[i] = val;
			}
                        std::cout << "Parameterized (two) constructor" << std::endl;

		}

		MyVector(const MyVector & other) : size{other.size}, capacity{other.capacity} {
			this -> data = new int[other.size];
			for(int i = 0; i < other.size; ++i) {
				this -> data[i] = other.data[i];
			}
                        std::cout << "Copy constructor" << std::endl;
		}

		MyVector(std::initializer_list<int> il) : size{il.size()}, capacity{il.size()}  {
			data = new int[size];
			int index = 0;
			for(int i : il) {
				data[index++] = i;
			}
                        std::cout << "Initializer_list constructor" << std::endl;
		}

		MyVector& operator=(const MyVector & other) {
			if(this == &other) {
				return *this;
			}
			if(data) {
				delete[] data;
			}
			this -> size = other.size;
			this -> capacity = other.capacity;
			data = new int[size];
			for(int i = 0; i < size; ++i) {
				this -> data[i] = other.data[i];
			}
                	std::cout << "Copy assignment operator" << std::endl;
			return *this;
		}

		MyVector(MyVector && other) : size{other.size}, capacity{other.capacity}, data{other.data} {
			other.data = nullptr;
			other.size = 0;
    			other.capacity = 0;
    			std::cout << "Move constructor" << std::endl;
		}
			
		MyVector &operator=(MyVector && other) {
			if(this == &other) return *this;
		 	delete[] data;
			data = other.data;
			size = other.size;
			capacity = other.capacity;

			other.data = nullptr;
			other.size = 0;
			other.capacity = 0;

			return *this;
		}	

		~MyVector() {
			delete[] data; 
    			std::cout << "Destructor" << std::endl;
		}
		
		int getSize() const {
			return size;		
		}

		int & operator[](size_t index) {
			return data[index];
		}

		const int & operator[](size_t index) const {
			return data[index];
		}

		int & front() {
			return data[0];
		}

		const int & front() const {
			return data[0];
		}

		int & back() {
			return data[size - 1];
		}

		const int & back() const {
			return data[size - 1];
		}
		
		bool empty() const {
			return size == 0;
		}

		void reserve(size_t new_cap) {
			if(new_cap <= capacity) {
				return;
			}
			int *new_data = new int[new_cap];
			for(int i = 0; i < size; ++i) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
			capacity = new_cap;
			return;
		}

		size_t getCapacity() const {
			return capacity;
		}

		void shrink_to_fit() {
			if(size == 0) {
				delete[] data;
			}
			if(size == capacity) {
				return;
			}
			int *new_data = new int[size];
			for(int i = 0; i < size; ++i) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
			capacity = size;
		}
		void clear() {
			size = 0;
		}

		size_t insert(size_t pos, int val) {
			if(pos > size) return size;
			if(size == capacity) {
				reserve(capacity + 1);
			}
			for(size_t i = size; i > pos; --i) {
				data[i] = data[i - 1];
			}
			data[pos] = val;
			return pos;		
		}

		size_t insert(size_t pos, size_t count, int val) {
                        if(pos > size) return size;
                        if(size == capacity) {
                                reserve(capacity + count);
                        }               
                        for(size_t i = size; i > pos; --i) {
                                data[i + count - 1] = data[i - 1];
                        }               
                        for(int i = pos; i < pos + count; ++i) {
				data[i] = val;
			}
                        return pos;
                }

		size_t insert(size_t pos, std::initializer_list<int> ilist) {
			if(pos > size) return size;
			size_t count = ilist.size();
			if(size + count > capacity) {
				reserve(size + count);
			}
			for(size_t i = size; i > pos; --i) {
				data[i + count - 1] = data[i - 1];
			}
			int index = pos;
			for(int elem : ilist) {
				data[index++] = elem;
			}
			size += count;
			return pos;
		}

		size_t erase(size_t pos) {
			if(pos > size) return size;
			for(size_t i = pos; i < size; ++i) {
				data[i] = data[i + 1];
			}
			--size;
			return pos;
		}

		size_t erase(size_t first, size_t last) {
			if(last > size) return size;
			size_t count = last - first;
			for(size_t i = last; i <= size; ++i) {
			       data[i - count] = data[i];
			}
			size -= count;
			return first;	
		}
	
		void push_back(int val) {
			if(size == capacity) reserve(capacity + 1);
			data[size] = val;
			++size;
			return;
		}

		void resize(size_t count) {
			if(count <= size) {
				size = count;     
				return;
			}
			if(count > capacity) {
				reserve(count);
			}
			for(size_t i = size; i < count; ++i) {
				data[i] = 0;
			}
			size = count;
			return;
		}

		void resize(size_t count, int val) {
                        if(count <= size) {
                                size = count;
                                return;
                        }
                        if(count > capacity) {
                                reserve(count);
                        }
                        for(size_t i = size; i < count; ++i) {
                                data[i] = val;
                        }
                        size = count;
                        return;
		}

		void swap(MyVector& other) {

			int * tmp_data = data;
			data = other.data;
			other.data = tmp_data;

			size_t tmp_size = size;
			size = other.size;
			other.size = tmp_size;

			size_t tmp_cap = capacity;
			capacity = other.capacity;
			other.capacity = tmp_cap;

			return;
		}

		void pop_back() {
			if(size > 0)
				--size;
		}
};































