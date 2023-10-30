/******************************************************
实验三：贪心算法问题1.最优子结构性质2.贪心选择性质
（1）一个问题最优解包含子问题最优解
（2）问题整体最优解由一系列局部最优解选择，
自顶向下，每一次贪心选择将问题简化为子问题
二、哈夫曼编码问题HuffmanCoding
Q:给定一个字符表C以及C中每个字符出现的频率表根据哈夫曼
编码规则求出具有最小平均码长的前缀树编码
INPUT：字母表C={c1,c2,...,cn}频率表F={f(c1),f(c2),...,f(cn)}
OUTPUT:具有最小平均码长B（T）的C的前缀编码树
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

struct HuffmanNode           // 哈夫曼树节点结构体
{    
    char data;                //保存具体字符数据
    int frequency;            //保存每个字符出现频率
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareHuffmanNodes                  // 用于比较两个哈夫曼节点的频率，以便在优先队列中按照频率升序排序
{                      
    bool operator()(HuffmanNode* a, HuffmanNode* b)
    {
        return a->frequency > b->frequency;       //保证返回的左子树节点频率小于右子树
    }
};

HuffmanNode* BuildHuffmanTree(std::map<char, int>& FrequencyTable)    // 生成哈夫曼树,通过“FrequencyTable”将字符映射到其出现的频率
{
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNodes> MinestFrequency; //存储当前具有最小频率的字符

    for (const auto& pair : FrequencyTable)       // 步骤 1: 创建优先队列（最小堆）并初始化
    {
        MinestFrequency.push(new HuffmanNode(pair.first, pair.second));
    }

    while (MinestFrequency.size() > 1)           // 步骤 2: 反复合并最小频率节点，直到只剩一个根节点
    {
        HuffmanNode* left = MinestFrequency.top(); //从 MinestFrequency 中弹出两个具有最小频率的节点，成为新树的左右子树。
        MinestFrequency.pop();
        HuffmanNode* right = MinestFrequency.top();
        MinestFrequency.pop();
                                                // 创建一个新节点，其频率为左右子节点频率之和，且没有字符数据
        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);  //用特殊字符 '$'代表内部非叶子节点
        newNode->left = left;
        newNode->right = right;
                                               // 将新节点插入优先队列中，继续迭代
        MinestFrequency.push(newNode);
    }
    return MinestFrequency.top();             // 步骤 3: 返回哈夫曼树的根节点
}

void PrintHuffmanCodes(HuffmanNode* root, std::string code, std::ofstream& outputFile) // 打印哈夫曼编码并将结果保存到文件
{
    if (!root)
        return;

    if (root->data != '$')     //叶子节点
    {
        outputFile << root->data << ": " << code << " (出现频率： " << root->frequency << ")\n";
    }
    PrintHuffmanCodes(root->left, code + "0", outputFile);
    PrintHuffmanCodes(root->right, code + "1", outputFile);
}

int main()
{
    int n;
    std::cout << "请输入要生成的字符个数: ";
    std::cin >> n;

    clock_t start = clock();
    std::map<char, int> FrequencyTable;
    std::string CharacterTable;
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < n; i++)
    {
        char RandomChar;
        int choice = rand() % 3;                  //随机生成字符串
        if (choice == 0)
        {
            RandomChar = '0' + rand() % 10;       // 生成随机数字
        }
        else if (choice == 1)
        {
            RandomChar = 'A' + rand() % 26;       // 生成随机大写字母
        }
        else
        {
            RandomChar = 'a' + rand() % 26;       // 生成随机小写字母
        }
        FrequencyTable[RandomChar]++;             //频率表存储每个字符出现的频率
        CharacterTable += RandomChar;             //字符表存储随机生成的字符
    }

    HuffmanNode* root = BuildHuffmanTree(FrequencyTable);   // 调用函数构建哈夫曼树
    std::string code = "";                          // 打印哈夫曼编码并将结果保存到文件
    std::ofstream outputFile("Huffman Code.txt");   //可在‘Huffman Code.txt’中查看哈夫曼编码表
    PrintHuffmanCodes(root, code, outputFile);
    outputFile.close();

    std::ofstream primarydata("primary code.txt");
    if (primarydata.is_open())
    {
        primarydata << CharacterTable;
        primarydata.close();
        std::cout << "初始数据已生成并存入primary code.txt" << std::endl;
        //std::cout << "生成的随机字符串: " << CharacterTable << std::endl;  // 输出生成的随机字符串
        std::cout << "随机字符串对应的哈夫曼编码及频率表已存入Huffman Code.txt中" << std::endl;
        clock_t end = clock();
        printf("查找时间: %lf\n", double(end - start) / CLOCKS_PER_SEC);
        return 0;
    }
}