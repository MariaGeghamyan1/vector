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
			this -> data = new int(other.size);
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
			this -> capacity = other.size;
			data = new int[size];
			for(int i = 0; i < size; ++i) {
				this -> data[i] = other.data[i];
			}
                	std::cout << "Copy assignment operator" << std::endl;
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
		void pop_back() {
			--size;
		}
};































