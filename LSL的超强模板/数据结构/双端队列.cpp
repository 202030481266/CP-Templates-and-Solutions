// 使用环来巧妙实现双端队列

class StaticDeque {
private:
    static const int MAX_SIZE = 1000005;
    int data[MAX_SIZE];
    int front, back;
    int count;

public:
    StaticDeque() {
        front = 0;
        back = 0;
        count = 0;
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == MAX_SIZE;
    }

    int size() const {
        return count;
    }

    void push_front(int value) {
        if (full()) {
            throw std::runtime_error("Deque is full");
        }
        
        // 向前移动front指针，注意循环
        front = (front - 1 + MAX_SIZE) % MAX_SIZE;
        data[front] = value;
        count++;
    }

    void push_back(int value) {
        if (full()) {
            throw std::runtime_error("Deque is full");
        }
        
        data[back] = value;
        // 向后移动back指针，注意循环
        back = (back + 1) % MAX_SIZE;
        count++;
    }

    int pop_front() {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        
        int value = data[front];
        // 向后移动front指针
        front = (front + 1) % MAX_SIZE;
        count--;
        return value;
    }

    int pop_back() {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        
        // 向前移动back指针
        back = (back - 1 + MAX_SIZE) % MAX_SIZE;
        count--;
        return data[back];
    }

    int front_value() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return data[front];
    }

    int back_value() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return data[(back - 1 + MAX_SIZE) % MAX_SIZE];
    }
};