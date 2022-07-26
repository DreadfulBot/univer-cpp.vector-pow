#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <time.h>

using namespace std;

vector<int> result;

void PrintVector(vector<int> vector) 
{
	for (int i = 0; i<vector.size(); i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}

void ClearZeros(vector<int> &vector)
{
	vector.erase(vector.end() - 1);
}

void CalculateModulo(vector<int> &dividend, vector<int> &divider, vector<int> &result, vector<int> &modulo)
{

	reverse(dividend.begin(), dividend.end());
	reverse(divider.begin(), divider.end());
	modulo = dividend;
	
	while (modulo.size() >= divider.size()) 
	{
		
		int offset = modulo.size() - divider.size();
		result.push_back(modulo.back());
		if (modulo.back() != 0)
			for (int i = offset++, j = 0; i < modulo.size(); i++, j++)
				modulo[i] = (modulo[i] ^ divider[j]);
		ClearZeros(modulo);
	}
	reverse(result.begin(), result.end());
}

vector<vector<int>> GetMatrix(vector<int> &g, int n)
{
	vector<vector<int>> resultMatrix;
	resultMatrix.resize(n-g.size()+1);
	for (int i = 0; i <= n - g.size(); i++)
		resultMatrix[i].resize(n);
	for (int i = 0; i <= n - g.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			resultMatrix[i][j]=0;
		}
		for (int j = i; j < i+g.size(); j++)
		{
			resultMatrix[i][j]=g[j - i];
		}
		for (int j = i + g.size(); j < n; j++)
		{
			resultMatrix[i][j] = 0;
		}
	}
	return resultMatrix;

}

void printMatrix(vector<vector<int>> matrix)
{
	cout << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

}

vector<int> coding(vector<vector<int>> matrix, vector<int> cod,int k)
{
	int count = pow(2, k);
	/*vector<vector<int>> code;
	code.resize(count);
	for (int i = 0; i < count; i++)
		code[i].resize(k);
	for (int i = 0; i < count; i++)
	{
		int chair = i;
		for (int j = 0; j < k; j++)
		{
			code[i][k - j - 1] = chair%2;
			chair = chair / 2;
			
		}
	}*/
	int row = matrix.size();
	int coll = matrix[0].size();

	vector<int> codeW;
	
	
	codeW.resize(coll);

	//for (int i = 0; i < coll; i++)
	{
		for (int j = 0; j < coll; j++)
			for (int l = 0; l < row; l++)
				codeW[j] += cod[l] * matrix[l][j];

	}
	for (int i = 0; i < coll; i++)
			codeW[i] = codeW[i] % 2;
	
	vector<int> sum;
	sum.resize(count);
	int min = coll;
	//for (int i = 1; i < count; i++)
	//{
	//	for (int j = 0; j < coll; j++)
	//		sum[i] += codeW[i][j];
	//	if (sum[i] < min)
	//		min = sum[i];
	//	cout << sum[i]<<endl;
	//}
	
	//cout << "min: " << min << endl;

	
	//printMatrix(codeW);
	return codeW;
}

vector<int> getSimbolCode(char a)
{
	vector<int> result;
	result.resize(8);
	int chair = a;
	for (int i = 0; i < 8; i++)
	{
		result[7-i] = chair % 2;
		chair = chair / 2;
	}
	return result;

}

void ReadAndGetCode(string srcFile, string dstFile) {
	char symbol;
	ifstream file(srcFile);
	ofstream dst(dstFile);
	while(!file.eof()) {
		file.get(symbol);
		vector<int> code =  getSimbolCode(symbol);
		for(int i = 0; i<8;i++)
		{
			if(code[i]==0)
				dst.put('0');
			else
				dst.put('1');
		}
	}
	file.close();
	dst.close();
}

void CodingFile(vector<vector<int>> matrix, string srcFile, string dstFile) {
	
	ifstream src(srcFile);
	ofstream dst(dstFile);
	while(!src.eof()) {
	vector<int> vec;
		for(int i=0; i<4; i++) {
			char c;
			src.get(c);
			vec.push_back(c == '0' ? 0 : 1);
		}
		vector<int> code = coding(matrix,vec,4);
		for(int i = 0; i<7;i++)
		{
			if(code[i]==0)
				dst.put('0');
			else
				dst.put('1');
		}
	}
	src.close();
	dst.close();
}

// test
void changeSymbols(string srcFile, string dstFile)
{
	srand (time(NULL));
	char symbol;
	ifstream file(srcFile);
	ofstream dst(dstFile);
	while(!file.eof()) {
		file.get(symbol);
		if(rand()%100 == 56)
			dst.put(symbol == '0' ? '1' : '0');
		else
			dst.put(symbol);
		
	}
	file.close();
	dst.close();
}
// test
int CalculateHeadpow(vector<int>& divider, vector<int>& modulo) {
	vector<int> temp(divider.size()+1, 0);
	int i=0;
	temp[0] = 1;
	temp[divider.size()] = 1;
	//vector<int> temp2;
	while(1) {
		i++;
		/*temp2.resize(result.size());
		for(int i=0; i<result.size(); i++)
			temp2[i]=result[i];*/
		CalculateModulo(temp, divider, result, modulo);
		if(find(modulo.begin(), modulo.end(), 1)==modulo.end())
			break;
		else {
			temp.pop_back();
			temp.push_back(0);
			temp.push_back(1);
		}
	}
	result.resize(temp.size()-divider.size()+1);
	//reverse(result.begin(), result.end());
	//for(int i=0; i<result.size(); i++)
	//	result[i]=temp2[temp.size() - i];
	return temp.size()-1;
}

int GetCodeWordLenght(vector<vector<int>> matrix) {
	// 0) найти поражд. матрицу (млад -> стар биты)
	// 1) все кодовые слова и посчитать их веса -> найти код расст -> кол-во исправл. ошибок
}

int main(void) 
{

	//vector<int> dividend = { 1, 1, 1, 1, 0, 0, 1, 1 };
	vector<int> dividend;
	dividend.push_back(1);
	dividend.push_back(1);
	dividend.push_back(0);
	dividend.push_back(1);
	//vector<int> divider = { 1, 0, 1, 1 };
	vector<int> divider;
	divider.push_back(1);
	divider.push_back(1);
	divider.push_back(0);
	divider.push_back(0);
	divider.push_back(1);
	divider.push_back(1);
	divider.push_back(1);
	divider.push_back(1);

	vector<int> modulo;

	//Делимое
	cout << "Dividend:" << endl;
	//Делитель
	PrintVector(dividend);
	cout << "Divider:" << endl;
	PrintVector(divider);

	int headpow = CalculateHeadpow(divider, modulo);
	cout << "Headpow: " << headpow << endl;
	cout << endl << "Result:" << endl;
	PrintVector(result);

	//CalculateModulo(dividend, divider, result, modulo);

	vector <vector<int>> matrix = GetMatrix(result, headpow);
	//coding(matrix, 4);
	printMatrix(matrix);


	/*vector<int> ch = getSimbolCode('a');
	int a = (int)'a';
	cout << "a: "<< a << " ";
	for (int i = 0; i < ch.size(); i++)
		cout << ch[i] << " ";
	cout << endl;*/
	
	
	/*cout << "Modulo:" << endl;
	PrintVector(modulo);*/

	/*ReadAndGetCode("timus.txt", "dst.txt");
	CodingFile(matrix, "dst.txt", "codefile.txt");

	changeSymbols("codefile.txt", "breakfile.txt");*/
	system("pause");
	return 0;
}