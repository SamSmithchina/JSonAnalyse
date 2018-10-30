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

//����json string ��class ����
JsonData JsonDataToJsonClass(const std::string strData)
{
	//�����õ�Json::reader 
	Json::Reader *readInfo = new Json::Reader(Json::Features::strictMode());
	JsonData jData;
	Json::Value rootJsonValue;
	//��ʼ
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

// ת�� class ���� to json �ַ���,
std::string ClassDataToJsonString(const JsonData  jData)
{
	Json::FastWriter writeInfo;
	Json::Value writeValue;
	
	//json����
	writeValue["id"] = jData.id;
	writeValue["time"] = jData.time;

	//Ƕ��
	Json::Value  subwriteValue;
	subwriteValue["count"] = jData.clsEle.count;
	subwriteValue["name"] = jData.clsEle.name;

	writeValue["data"] = subwriteValue;

	//ת��string
	std::string strInfo = writeInfo.write(writeValue);

	std::cout << __FUNCTION__ << "  ת������� ��" << std::endl << strInfo << std::endl;
	return strInfo;
}

//���ļ�����ȡjson �ַ���
std::string ReadJsonData(const std::string& strFileName)
{
	std::fstream ifstreamRead(strFileName, std::ios::in);
	if (!ifstreamRead)
	{
		std::cerr << __FUNCTION__ << "�� " << strFileName << " ʧ�ܣ�" << std::endl;
	}
	
	std::string strReadRes;
	try
	{
		getline(ifstreamRead, strReadRes); 
		//������Ҫע�⣺ ԭ�е�ofstream<< �ļ���ʽ��ȡ�������������ļ����пո�ʽ��ֹͣ��
		//���� �Ľ�ʹ�� getline(ofstream , string);���ȡ�������ַ���
	}
	catch (std::exception e)
	{
		throw(e);
	}

	ifstreamRead.close();
	std::cout << __FUNCTION__ << "  ��ȡ " << strFileName << "  ��ɣ�"
		<< std::endl << strReadRes << std::endl;
	return strReadRes;
}

//д�ļ��� д class JsonData �� jsondata.txt
std::string WriteJSonString(const std::string& strFileName, JsonData& jData)
{
	std::string strWriteRes = ClassDataToJsonString(jData);
	std::fstream ofstreamWrite(strFileName, std::ios::out);
	if (!ofstreamWrite)
	{
		std::cerr << __FUNCTION__ << "��  " <<  strFileName << "  ����" << std::endl;
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
	std::cout << __FUNCTION__ << "  д�� " << strFileName << "  ��ɣ�"
		<< std::endl << strWriteRes << std::endl;
	return strWriteRes;
}
