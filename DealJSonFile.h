// 读取json.txt文件，  解析json字符串消息源jsonsource.txt ， 将解析结果写回jsondata.txt
// 或者将 c++ string 转换成json 格式
// 这里注意数据结构和编译原理
#ifndef __DEALJSONFILE_H__
#define __DEALJSONFILE_H__

#include "json/json.h"
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#include <iostream>
#include <string>
#include <iomanip>

struct Data
{
	int count;
	std::string name;
};

struct JsonData
{
	Data clsEle;
	int id;
	std::string time;
	JsonData operator=(const JsonData& jData);
	int CompareEqual(const JsonData& jData);
	friend std::ostream& operator <<(std::ostream &output, JsonData jData);
};

//解析json string 成class 对象
JsonData JsonDataToJsonClass(const std::string strData);

// 转换 class 对象 to json字符串
std::string ClassDataToJsonString(const JsonData  jData);

//读文件，获取json 字符串
std::string ReadJsonData(const std::string& strFileName);

//写文件， 写 class JsonData 到 jsondata.txt
std::string WriteJSonString(const std::string& strFileName, JsonData& jData);

#endif __DEALJSONFILE_H__