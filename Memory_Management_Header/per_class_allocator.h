#pragma once
namespace per_class_allocator {

	void per_class_allocator_function();
	class Screen {
	public:
		Screen(int x) : i(x) {};
		int get() { return i; }
		void*  operator new(size_t);
		void operator delete(void*, size_t);
	private:
		Screen * next;  //又多申请4个字节，膨胀百分百，降低malloc的次数，去除cookie,第一版多耗用一个next指针
		static Screen* freeStore;
		static const int screenChunk;
	private:
		int i;
	};
}