#include "DealJSonFile.h"
#include <iostream>
#include <string>
#include <time.h>

int main()
{
	std::string strJsonSourceFileName = "jsonsource.txt";
	JsonData jData;
	jData.id = 161340111;

	//生成当前时间
	time_t now;
	tm tmPtr;
	time(&now);
	localtime_s(&tmPtr, &now);

	char chTemp[9] = { "\0" };
	_Strftime(chTemp, 9, "%Y%m%d", &tmPtr, NULL);	//char 8
	jData.time = chTemp;						//日期年月日
	jData.time += " ";
	_Strftime(chTemp, 9, "%H:%M:%S", &tmPtr, NULL);	//char 8  字符串末尾填充空位；
	jData.time += chTemp;

	jData.clsEle.count = 1;
	jData.clsEle.name = "cpp";

	//把json 对象转成string字符串 ，写到 jsonsource.txt
	std::string strWriteRes = WriteJSonString(strJsonSourceFileName, jData);

	//读取上一次操作 jsonsource.txt的字符串结果，转换成class json data
	std::string strReadRes = ReadJsonData(strJsonSourceFileName);
	JsonData jDataAfterTrans = JsonDataToJsonClass(strReadRes);

	//将json  string 字符串 转换成 json 对象

	//比较处理前后的结果
	std::cout << "jDataAfterTrans.CompareEqual(jData) : " << jDataAfterTrans.CompareEqual(jData) << std::endl;

	std::cout << "处理前  ： " << std::endl << jData
		<< "处理后  ： " << std::endl << jDataAfterTrans
		<< std::endl;

	system("pause");
	return 0;
}