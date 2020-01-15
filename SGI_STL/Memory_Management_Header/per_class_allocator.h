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
		Screen * next;  //�ֶ�����4���ֽڣ����Ͱٷְ٣�����malloc�Ĵ�����ȥ��cookie,��һ������һ��nextָ��
		static Screen* freeStore;
		static const int screenChunk;
	private:
		int i;
	};
}