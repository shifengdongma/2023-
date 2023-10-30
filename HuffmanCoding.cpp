/******************************************************
ʵ������̰���㷨����1.�����ӽṹ����2.̰��ѡ������
��1��һ���������Ž�������������Ž�
��2�������������Ž���һϵ�оֲ����Ž�ѡ��
�Զ����£�ÿһ��̰��ѡ�������Ϊ������
������������������HuffmanCoding
Q:����һ���ַ���C�Լ�C��ÿ���ַ����ֵ�Ƶ�ʱ���ݹ�����
����������������Сƽ���볤��ǰ׺������
INPUT����ĸ��C={c1,c2,...,cn}Ƶ�ʱ�F={f(c1),f(c2),...,f(cn)}
OUTPUT:������Сƽ���볤B��T����C��ǰ׺������
LI YANG 2021065408
2023.10.14
******************************************************/


#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

struct HuffmanNode           // ���������ڵ�ṹ��
{    
    char data;                //��������ַ�����
    int frequency;            //����ÿ���ַ�����Ƶ��
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareHuffmanNodes                  // ���ڱȽ������������ڵ��Ƶ�ʣ��Ա������ȶ����а���Ƶ����������
{                      
    bool operator()(HuffmanNode* a, HuffmanNode* b)
    {
        return a->frequency > b->frequency;       //��֤���ص��������ڵ�Ƶ��С��������
    }
};

HuffmanNode* BuildHuffmanTree(std::map<char, int>& FrequencyTable)    // ���ɹ�������,ͨ����FrequencyTable�����ַ�ӳ�䵽����ֵ�Ƶ��
{
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNodes> MinestFrequency; //�洢��ǰ������СƵ�ʵ��ַ�

    for (const auto& pair : FrequencyTable)       // ���� 1: �������ȶ��У���С�ѣ�����ʼ��
    {
        MinestFrequency.push(new HuffmanNode(pair.first, pair.second));
    }

    while (MinestFrequency.size() > 1)           // ���� 2: �����ϲ���СƵ�ʽڵ㣬ֱ��ֻʣһ�����ڵ�
    {
        HuffmanNode* left = MinestFrequency.top(); //�� MinestFrequency �е�������������СƵ�ʵĽڵ㣬��Ϊ����������������
        MinestFrequency.pop();
        HuffmanNode* right = MinestFrequency.top();
        MinestFrequency.pop();
                                                // ����һ���½ڵ㣬��Ƶ��Ϊ�����ӽڵ�Ƶ��֮�ͣ���û���ַ�����
        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);  //�������ַ� '$'�����ڲ���Ҷ�ӽڵ�
        newNode->left = left;
        newNode->right = right;
                                               // ���½ڵ�������ȶ����У���������
        MinestFrequency.push(newNode);
    }
    return MinestFrequency.top();             // ���� 3: ���ع��������ĸ��ڵ�
}

void PrintHuffmanCodes(HuffmanNode* root, std::string code, std::ofstream& outputFile) // ��ӡ���������벢��������浽�ļ�
{
    if (!root)
        return;

    if (root->data != '$')     //Ҷ�ӽڵ�
    {
        outputFile << root->data << ": " << code << " (����Ƶ�ʣ� " << root->frequency << ")\n";
    }
    PrintHuffmanCodes(root->left, code + "0", outputFile);
    PrintHuffmanCodes(root->right, code + "1", outputFile);
}

int main()
{
    int n;
    std::cout << "������Ҫ���ɵ��ַ�����: ";
    std::cin >> n;

    clock_t start = clock();
    std::map<char, int> FrequencyTable;
    std::string CharacterTable;
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < n; i++)
    {
        char RandomChar;
        int choice = rand() % 3;                  //��������ַ���
        if (choice == 0)
        {
            RandomChar = '0' + rand() % 10;       // �����������
        }
        else if (choice == 1)
        {
            RandomChar = 'A' + rand() % 26;       // ���������д��ĸ
        }
        else
        {
            RandomChar = 'a' + rand() % 26;       // �������Сд��ĸ
        }
        FrequencyTable[RandomChar]++;             //Ƶ�ʱ�洢ÿ���ַ����ֵ�Ƶ��
        CharacterTable += RandomChar;             //�ַ���洢������ɵ��ַ�
    }

    HuffmanNode* root = BuildHuffmanTree(FrequencyTable);   // ���ú���������������
    std::string code = "";                          // ��ӡ���������벢��������浽�ļ�
    std::ofstream outputFile("Huffman Code.txt");   //���ڡ�Huffman Code.txt���в鿴�����������
    PrintHuffmanCodes(root, code, outputFile);
    outputFile.close();

    std::ofstream primarydata("primary code.txt");
    if (primarydata.is_open())
    {
        primarydata << CharacterTable;
        primarydata.close();
        std::cout << "��ʼ���������ɲ�����primary code.txt" << std::endl;
        //std::cout << "���ɵ�����ַ���: " << CharacterTable << std::endl;  // ������ɵ�����ַ���
        std::cout << "����ַ�����Ӧ�Ĺ��������뼰Ƶ�ʱ��Ѵ���Huffman Code.txt��" << std::endl;
        clock_t end = clock();
        printf("����ʱ��: %lf\n", double(end - start) / CLOCKS_PER_SEC);
        return 0;
    }
}