#pragma once
#include <string>
namespace macro_static_allocator {

	//���allocator1��ȥ��װmalloc��delete
	class allocator1 {
	private:
		struct obj {
			struct obj*next; //Ƕ��ʽָ�� embedded pointer
		};
	public:
		void* allocate(size_t);
		void deallocate(void*, size_t);
	private:
		obj * freeStore = nullptr;
		const int CHUNK = 5; //СһЩ�Ա�۲�
	};

//��myAlloc.allocateת��Ϊ�궨��
	//DECLARE_POOL_ALLOC --used in class definition
	//�÷�б��������
#define DECLARE_POOL_ALLOC() \
public:\
	void* operator new(size_t size) { return myAlloc.allocate(size); } \
	void operator delete(void* p) { myAlloc.deallocate(p, 0); } \
protected: \
	static allocator1 myAlloc;

	//IMPLEMENT_POOL_ALLOC--used in class implementation file
#define IMPLEMENT_POOL_ALLOC(class_name) \
	allocator1 class_name::myAlloc;

	//�������ڲ��Ե��� Foo
	class Foo {
		DECLARE_POOL_ALLOC()
	public:
		long L;
		std::string str;
	public:
		Foo(long l) :L(l) {}
	};


	void macro_static_allocator_function();
}