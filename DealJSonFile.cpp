#include "DealJSonFile.h"
#include <fstream>


JsonData JsonData::operator=(const JsonData& jData)
{
	this->id = jData.id;
	this->time = jData.time;
	this->clsEle.count = jData.clsEle.count;
	this->clsEle.name = jData.clsEle.name;
	return *this;
}

int JsonData::CompareEqual(const JsonData& jData)
{
	if (this->id != jData.id)
	{
		return -1;
	}
	if (this->time != jData.time)
	{
		return -1;
	}
	if (this->clsEle.count != jData.clsEle.count)
	{
		return -1;
	}
	if (this->clsEle.name != jData.clsEle.name)
	{
		return -1;
	}
	return 0;
}

std::ostream& operator <<(std::ostream &output, JsonData jData)
{
	output << std::setiosflags(std::ios::left)
		<< std::setw(14) << "id" << jData.id << std::endl
		<< std::setw(14) << "time" << jData.time << std::endl
		<< std::setw(14) << "data.count" << jData.clsEle.count << std::endl
		<< std::setw(14) << "data.name" << jData.clsEle.name << std::endl;
	return output;
}

// https://blog.csdn.net/u011261430/article/details/77713299/

//解析json string 成class 对象
JsonData JsonDataToJsonClass(const std::string strData)
{
	//解析用的Json::reader 
	Json::Reader *readInfo = new Json::Reader(Json::Features::strictMode());
	JsonData jData;
	Json::Value rootJsonValue;
	//开始
	if (readInfo->parse(strData, rootJsonValue))
	{
		if (rootJsonValue["id"].isInt())
		{
			jData.id = rootJsonValue["id"].asInt();
		}

		if (rootJsonValue["time"].isString())
		{
			jData.time = rootJsonValue["time"].asString();
		}


		if (rootJsonValue["data"]["count"].isInt())
		{
			jData.clsEle.count = rootJsonValue["data"]["count"].asInt();
		}
		
		if (rootJsonValue["data"]["name"].isString())
		{
			jData.clsEle.name = rootJsonValue["data"]["name"].asString();
		}
	}
	delete readInfo;
	return jData;
}

// 转换 class 对象 to json 字符串,
std::string ClassDataToJsonString(const JsonData  jData)
{
	Json::FastWriter writeInfo;
	Json::Value writeValue;
	
	//json对象
	writeValue["id"] = jData.id;
	writeValue["time"] = jData.time;

	//嵌套
	Json::Value  subwriteValue;
	subwriteValue["count"] = jData.clsEle.count;
	subwriteValue["name"] = jData.clsEle.name;

	writeValue["data"] = subwriteValue;

	//转成string
	std::string strInfo = writeInfo.write(writeValue);

	std::cout << __FUNCTION__ << "  转换结果是 ：" << std::endl << strInfo << std::endl;
	return strInfo;
}

//读文件，获取json 字符串
std::string ReadJsonData(const std::string& strFileName)
{
	std::fstream ifstreamRead(strFileName, std::ios::in);
	if (!ifstreamRead)
	{
		std::cerr << __FUNCTION__ << "打开 " << strFileName << " 失败！" << std::endl;
	}
	
	std::string strReadRes;
	try
	{
		getline(ifstreamRead, strReadRes); 
		//这里需要注意： 原有的ofstream<< 文件流式读取方法，在遇到文件中有空格式会停止；
		//这里 改进使用 getline(ofstream , string);会读取完整的字符；
	}
	catch (std::exception e)
	{
		throw(e);
	}

	ifstreamRead.close();
	std::cout << __FUNCTION__ << "  读取 " << strFileName << "  完成！"
		<< std::endl << strReadRes << std::endl;
	return strReadRes;
}

//写文件， 写 class JsonData 到 jsondata.txt
std::string WriteJSonString(const std::string& strFileName, JsonData& jData)
{
	std::string strWriteRes = ClassDataToJsonString(jData);
	std::fstream ofstreamWrite(strFileName, std::ios::out);
	if (!ofstreamWrite)
	{
		std::cerr << __FUNCTION__ << "打开  " <<  strFileName << "  出错！" << std::endl;
	}
	try
	{
		ofstreamWrite << strWriteRes;
	}
	catch (std::exception & e)
	{
		throw(e);
	}

	ofstreamWrite.close();
	std::cout << __FUNCTION__ << "  写入 " << strFileName << "  完成！"
		<< std::endl << strWriteRes << std::endl;
	return strWriteRes;
}
