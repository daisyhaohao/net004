#ifndef BLOB_H
#define BLOB_H
#include <string>
struct Blob{
	public:
	~Blob();
	void set_shape(const Blob& b);
	void set_shape(int n, int c, int h, int w);
	void set_data(float * data);
	void alloc();
	void clear();
	void show() const;
	int nchw() const;
	int chw() const;
	int hw() const;

	public:
	float *data = 0;
	int n = 0, c = 0, w = 0, h = 0;
	std::string type;
	
	private:
	bool owner = true;
};
#endif
