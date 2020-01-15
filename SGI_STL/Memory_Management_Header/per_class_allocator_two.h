#pragma once
namespace per_class_allocator_two {
	void per_class_allocator_two_function();

	class Airplane {
	private:
		struct AirplaneRep {
			unsigned long miles;
			char type;
		};
	private:
		union { 
			AirplaneRep rep;
			Airplane* next; //借用同一个东西的前四个字节作为指针来用
		};
	public:
		unsigned long getMiles() { return rep.miles; }
		char getType() { return rep.type; }
		void set(unsigned long m, char t) {
			rep.miles = m; 
			rep.type = t;
		}
	public:
		static void* operator new(size_t size);
		static void operator delete(void* deadObject, size_t size);
	private:
		static const int BLOCK_SIZE;
		static Airplane* headOfFreeList;
	};
}