#ifndef BASERUN_H
#define BASERUN_H
#include "Net004.h"
#include "JsonParser.h"
class Run{
	public:
	Run();
	Run(const JsonValue& j);
	virtual void operator()(Net004& net, int cur) = 0;
	virtual void show()const;
	virtual void check(const Net004& net) const;

	private:
	std::string type, name;
	int iter = 1, iter_interval = 1;
	JsonValue j_;
};
#endif
