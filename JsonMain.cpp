#include "DealJSonFile.h"
#include <iostream>
#include <string>
#include <time.h>

int main()
{
	std::string strJsonSourceFileName = "jsonsource.txt";
	JsonData jData;
	jData.id = 161340111;

	//���ɵ�ǰʱ��
	time_t now;
	tm tmPtr;
	time(&now);
	localtime_s(&tmPtr, &now);

	char chTemp[9] = { "\0" };
	_Strftime(chTemp, 9, "%Y%m%d", &tmPtr, NULL);	//char 8
	jData.time = chTemp;						//����������
	jData.time += " ";
	_Strftime(chTemp, 9, "%H:%M:%S", &tmPtr, NULL);	//char 8  �ַ���ĩβ����λ��
	jData.time += chTemp;

	jData.clsEle.count = 1;
	jData.clsEle.name = "cpp";

	//��json ����ת��string�ַ��� ��д�� jsonsource.txt
	std::string strWriteRes = WriteJSonString(strJsonSourceFileName, jData);

	//��ȡ��һ�β��� jsonsource.txt���ַ��������ת����class json data
	std::string strReadRes = ReadJsonData(strJsonSourceFileName);
	JsonData jDataAfterTrans = JsonDataToJsonClass(strReadRes);

	//��json  string �ַ��� ת���� json ����

	//�Ƚϴ���ǰ��Ľ��
	std::cout << "jDataAfterTrans.CompareEqual(jData) : " << jDataAfterTrans.CompareEqual(jData) << std::endl;

	std::cout << "����ǰ  �� " << std::endl << jData
		<< "�����  �� " << std::endl << jDataAfterTrans
		<< std::endl;

	system("pause");
	return 0;
}