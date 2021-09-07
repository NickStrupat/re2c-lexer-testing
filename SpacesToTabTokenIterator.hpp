#pragma once

#include <cstdint>
#include <exception>

#include "Token.hpp"

template<typename T, uint8_t Capacity>
class StaticCapacityQueue {
	T items[Capacity];
	uint8_t front;
	uint8_t back;
	uint8_t count;
public:
	StaticCapacityQueue() : items(), front(), back(), count() {}

	uint8_t size() const { return count; }
	bool isEmpty() const { return count == 0; }
	bool isFull() const { return count == Capacity; }

	void clear() { front = 0; back = 0; count = 0; }

	void pushBack(T item) {
		if (isFull())
			throw runtime_error("Queue is full.");
		items[back] = item;
		back = (back + 1) % Capacity;
		count++;
	}

	T popFront() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		T hold = items[front];
		front = (front + 1) % Capacity;
		count--;
		return hold;
	}

	T peekBack() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		return items[front];
	}

	T peekFront() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		return items[front];
	}
};

template<typename TokenIterator, uint8_t MaxSpaceCount = 8>
class SpacesToTabTokenIterator {
	StaticCapacityQueue<Token, MaxSpaceCount> queue;
	uint8_t _spacesCount;
	TokenIterator it;
public:
	SpacesToTabTokenIterator(TokenIterator it, uint8_t spacesCount = 4) : queue(), _spacesCount(spacesCount), it(it) {}

	uint8_t spacesCount() const { return _spacesCount; }
	uint8_t spacesCount(uint8_t spacesCount) { _spacesCount = spacesCount; }

	Token next() {
		if (queue.size() != 0 && queue.peekBack().type != TokenType::Whitespace)
			return queue.popFront();

		for (;;) {
			Token token = it.next();
			queue.pushBack(token);

			if (token.type == TokenType::Whitespace) {
				if (queue.size() == spacesCount()) {
					auto start = queue.peekFront().sv.data();
					size_t length = 0;
					while (!queue.isEmpty())
						length += queue.popFront().sv.length();
					Token syntheticTab{ TokenType::Tab, { start, length } };
					queue.clear();
					return syntheticTab;
				}
				else {
					continue;
				}
			}
			else {
				return queue.popFront();
			}
		}
	}
};