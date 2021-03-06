#include <fstream>
#include <sstream>
#include "Parser.h"
#include "Net004.h"
#include <stack>
using namespace std;
ModelParser::ModelParser(){
}
void ModelParser::read_model(const std::string& path, Net004* net){
	FILE* file = fopen(path.c_str(), "rb");
	while(!feof(file)){
		char buffer[100],layer_name[100],data_name[100];
		int n;
		fread(buffer, sizeof(char), 100, file);
		sscanf(buffer,"%s %s %d",layer_name,data_name,&n);
		//printf("%s %s %d\n",layer_name,data_name,n);
		Blob& b = net->operator[](layer_name)->params[data_name];
		if(n!=b.nchw()){
			printf("blob size different %d (%d * %d * %d * %d -> %d)\n",n,b.n,b.c,b.h,b.w,b.nchw());
			exit(0);
		}
		fread(b.data,sizeof(float),n,file);
	}
	fclose(file);
}
void ModelParser::write_model(const std::string& path, Net004* net){
	FILE* file = fopen(path.c_str(), "wb");
	for(int i=0;i<net->ls.size();++i){
		Layer* layer = net->ls[i];
		for(const auto& j:layer->params){
			char buffer[100];
			sprintf(buffer,"%s %s %d",layer->name.c_str(),j.first.c_str(),j.second.nchw());
			fwrite(buffer, sizeof(char), 100, file);
			fwrite(j.second.data, sizeof(float), j.second.nchw(), file);
		}
	}
	fclose(file);
}
