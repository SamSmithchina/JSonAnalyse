// ��ȡjson.txt�ļ���  ����json�ַ�����ϢԴjsonsource.txt �� ���������д��jsondata.txt
// ���߽� c++ string ת����json ��ʽ
// ����ע�����ݽṹ�ͱ���ԭ��
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

//����json string ��class ����
JsonData JsonDataToJsonClass(const std::string strData);

// ת�� class ���� to json�ַ���
std::string ClassDataToJsonString(const JsonData  jData);

//���ļ�����ȡjson �ַ���
std::string ReadJsonData(const std::string& strFileName);

//д�ļ��� д class JsonData �� jsondata.txt
std::string WriteJSonString(const std::string& strFileName, JsonData& jData);

#endif __DEALJSONFILE_H__