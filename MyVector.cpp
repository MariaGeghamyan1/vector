#include <iostream>
#include <initializer_list>

template <typename T> 
class MyVector {
	private: 
		T * data;
		size_t size;
		size_t capacity;
	public:
		MyVector() : data(nullptr), size(0), capacity(0) {
			std::cout << "Default constructor" << std::endl;
		};

		MyVector(size_t size) : MyVector(size, T{}) {
                        std::cout << "Parameterized (one) constructor" << std::endl;
		}

		MyVector(size_t size, T val) : size{size}, capacity{size} {
			data = new T[size];
			for(size_t i = 0; i < size; ++i) {
				data[i] = val;
			}
                        std::cout << "Parameterized (two) constructor" << std::endl;

		}

		MyVector(const MyVector & other) : size{other.size}, capacity{other.capacity} {
			this -> data = new T[other.capacity];
			for(size_t i = 0; i < other.size; ++i) {
				this -> data[i] = other.data[i];
			}
                        std::cout << "Copy constructor" << std::endl;
		}

		MyVector(std::initializer_list<T> il) : size{il.size()}, capacity{il.size()}  {
			data = new T[size];
			size_t index = 0;
			for(const T& val : il) {
				data[index++] = val;
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
			data = new T[size];
			for(size_t i = 0; i < size; ++i) {
				this -> data[i] = other.data[i];
			}
                	std::cout << "Copy assignment operator" << std::endl;
			return *this;
		}

		MyVector(MyVector && other) noexcept : size{other.size}, capacity{other.capacity}, data{other.data} {
			other.data = nullptr;
			other.size = 0;
    			other.capacity = 0;
    			std::cout << "Move constructor" << std::endl;
		}
			
		MyVector &operator=(MyVector && other) noexcept {
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

		bool operator==(const MyVector & rhs) const {
			if(this -> size != rhs.size)
			       return false;
			 for(size_t i = 0; i < this -> size; ++i) {
				 if(this -> data[i] != rhs.data[i]) 
					 return false;
			 }
			 return true;
		}
		
		bool operator<(const MyVector & rhs) const {
			size_t min_size = std::min(this->size, rhs.size);
                        for(size_t i = 0; i < min_size; ++i) {
                                 if(this -> data[i] > rhs.data[i]) 
                                         return false;
				 else if( this -> data[i] < rhs.data[i]) 
					return true;
                         }
                         return this-> size < rhs.size;
                }

		friend std::ostream & operator<<(std::ostream & os, const MyVector & obj) {
			for(size_t i = 0; i < obj.size; ++i) {
				os << obj.data[i] << " ";
			}
			os << std::endl;
			return os;
		}

		friend std::istream & operator>>(std::istream & is,  MyVector & obj) {
			for(size_t i = 0; i < obj.size; ++i) {
				is >> obj.data[i];
			}
			return is;
		}

		~MyVector() {
			delete[] data; 
    			std::cout << "Destructor" << std::endl;
		}
		
		size_t getSize() const {
			return size;		
		}

		T& operator[](size_t index) {
			if(index >= size) throw std::out_of_range("Index out of range");
			return data[index];
		}

		const T& operator[](size_t index) const {
			if(index >= size) throw std::out_of_range("Index out of range");
			return data[index];
		}

		T& front() {
			if(size == 0) throw std::out_of_range("empty vector");
			return data[0];
		}

		const T& front() const {
			if(size == 0) throw std::out_of_range("empty vector");
			return data[0];
		}

		T& back() {
			if(size == 0) throw std::out_of_range("empty vector");
			return data[size - 1];
		}

		const T& back() const {
			if(size == 0) throw std::out_of_range("empty vector");
			return data[size - 1];
		}
		
		bool empty() const {
			return size == 0;
		}

		void reserve(size_t new_cap) {
			if(new_cap <= capacity) {
				return;
			}
			T *new_data = new T[new_cap];
			for(size_t i = 0; i < size; ++i) {
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
				data = nullptr;
				capacity = 0;
				return;
			}
			if(size == capacity) {
				return;
			}
			T *new_data = new T[size];
			for(size_t i = 0; i < size; ++i) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
			capacity = size;
		}
		void clear() {
			for(size_t i = 0; i < size; ++i) {
			    data[i].~T();
			}	
			size = 0;

		}

		size_t insert(size_t pos, T val) {
			if(pos > size) return size;
			if(size == capacity) {
			        reserve(capacity == 0 ? 1 : capacity * 2);
			}
			for(size_t i = size; i > pos; --i) {
				data[i] = data[i - 1];
			}
			data[pos] = val;
			++size;
			return pos;		
		}

		size_t insert(size_t pos, size_t count, T val) {
                        if(pos > size) return size;
                        if(size + count > capacity) {
				reserve(capacity == 0 ? count : std::max(capacity * 2, size + count));
                        }               
                        for(size_t i = size; i > pos; --i) {
                                data[i + count - 1] = data[i - 1];
                        }               
                        for(size_t i = pos; i < pos + count; ++i) {
				data[i] = val;
			}
			size += count;
                        return pos;
                }

		size_t insert(size_t pos, std::initializer_list<T> ilist) {
			if(pos > size) return size;
			size_t count = ilist.size();
			if(size + count > capacity) {
				reserve(std::max(capacity * 2, size + count));
			}
			for(size_t i = size; i > pos; --i) {
				data[i + count - 1] = data[i - 1];
			}
			size_t index = pos;
			for(const T& val : ilist) {
				data[index++] = val;
			}
			size += count;
			return pos;
		}

		size_t erase(size_t pos) {
			if(pos >= size) return size;
			for(size_t i = pos; i < size - 1; ++i) {
				data[i] = data[i + 1];
			}
			--size;
			data[size].~T();
			return pos;
		}

		size_t erase(size_t first, size_t last) {
			if(first >= size || first >= last) return size;
			size_t count = last - first;
			size_t old_size = size;
			for(size_t i = last; i < old_size; ++i) {
			       data[i - count] = data[i];
			}
			for(size_t i = old_size - count; i < old_size; ++i) {
				data[i].~T();
			}
			size -= count;
			return first;	
		}
	
		void push_back(T val) {
			if(size == capacity) reserve(capacity == 0 ? 1 : capacity * 2);
			data[size] = val;
			++size;
			return;
		}

		void resize(size_t count) {
			if(count < size) {
				for(size_t i = count; i < size; ++i) {
					data[i].~T();
    				}
				size = count;     
				return;
			}
			if(count > capacity) {
				reserve(count);
			}
			for(size_t i = size; i < count; ++i) {
				data[i] = T{};
			}
			size = count;
			return;
		}

		void resize(size_t count, T val) {
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

			T * tmp_data = data;
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
			if(size > 0) {
				--size;
				data[size].~T();
			}
			return;
		}
};































