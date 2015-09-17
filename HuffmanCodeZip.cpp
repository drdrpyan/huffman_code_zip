#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include "BGM_BinaryTree.h"
#include "BGM_temp_BitStream.h"
using namespace std;
using BGM::DataStructure::BinaryTree;
using BGM::DataStructure::BinaryTreeNode;
using BGM::temp::BitStream;

typedef pair<char, unsigned long long> hSym;
typedef pair<unsigned long long, BinaryTreeNode<char>*> qNode;

bool operator<(const qNode& node1, const qNode& node2)
{
	return node1.first < node2.first;
}

struct cmp
{
	bool operator()(const qNode& node1, const qNode& node2)
	{
		return node1.first > node2.first;
	}
};

class HuffmanCodeZip
{
private:
	void codeTraverse(BinaryTreeNode<char> *node, vector<bool> *codeBuffer, vector<bool> *eachCode)
	{
		if(node->isTerminal())
		{
			for(int i=0; i<codeBuffer->size(); i++)
				eachCode[(unsigned char)node->getData()].push_back((*codeBuffer)[i]);

			return;
		}
		else
		{
			codeBuffer->push_back(false);
			codeTraverse(node->getLeftChildPtr(), codeBuffer, eachCode);
			codeBuffer->pop_back();
			codeBuffer->push_back(true);
			codeTraverse(node->getRightChildPtr(), codeBuffer, eachCode);
			codeBuffer->pop_back();
		}
	}
	BinaryTree<char>* makeHuffmanCodeTree(vector<qNode*>& qNodeTab)
	{
		//make tree
		qNode node1, node2, *newQN;
		unsigned long long newFreq;
		BinaryTreeNode<char>* newBTN;
		priority_queue<qNode, vector<qNode>, cmp> pq;

		for(int i=0; i<256; i++)
			pq.push(*qNodeTab[i]);

		while(pq.size() > 1)
		{
			node1 = pq.top();
			pq.pop();
			node2 = pq.top();
			pq.pop();

			newFreq = node1.first + node2.first;
			newBTN = new BinaryTreeNode<char>(node1.second, 0, node2.second);
			newQN = new qNode(newFreq, newBTN);
			qNodeTab.push_back(newQN);
			pq.push(*newQN);
		}

		BinaryTree<char> *huffmanTree = new BinaryTree<char>(pq.top().second);
		return huffmanTree;
	}
public:
	void compress(ifstream& is, ofstream& os)
	{
		//init
		vector<qNode*> qNodeTab;
		for(int i=0; i<256; i++)
		{
			qNodeTab.push_back(new qNode(0, new BinaryTreeNode<char>((char)i)));
		}	

		//scan input file, make frequency table
		unsigned long long totalCharNum = 0;
		char asciiSym;
		while(is.good())
		{
			is.get(asciiSym);
			qNodeTab[asciiSym]->first++;
			totalCharNum++;
		}		

		//make code tree		
		BinaryTree<char>* hcTree = makeHuffmanCodeTree(qNodeTab);

		//make code table
		vector<bool> code[256];
		vector<bool> *codeBuffer = new vector<bool>;
		BinaryTreeNode<char> *cursor = hcTree->getRootPtr();
		codeTraverse(cursor, codeBuffer, code);

		//print header
		unsigned long long freqs[256];
		for(int i=0; i<256; i++)
			freqs[i] = qNodeTab[i]->first;
		os.write((char*)freqs, sizeof(freqs));

		//print body
		is.clear();
		is.seekg(0, ios::end);
		long fileSize = is.tellg();
		is.clear();
		is.seekg( 0, std::ios_base::beg);
		int cnt = 0;
		BitStream bs;
		while((long)is.tellg() != fileSize)
		{
			is.read(&asciiSym, 1);
			bs.push(code[(unsigned char)asciiSym]);
			if(++cnt == 100)
			{
				bs.print(os);
				cnt = 0;
			}
		}
		bs.print(os);
		bs.flush(os);

		

		//print inforamtion
		cout << "total char # : " << totalCharNum << endl;
		cout << "frequency of each char" << endl;
		for(int i=32; i<128; i++)
			printf("Dec : %d  Hex : %x  Char : %c  Freq : %llu\n", i, i, (char)i, qNodeTab[i]->first);
		cout << "compress rate : " << ((float)os.tellp()/(float)is.tellg()) * 100.0 << '%' << endl;

		//delete heap objects
		hcTree->clear();
		delete hcTree;
		for(int i=0; i<qNodeTab.size(); i++)
			delete qNodeTab[i];

		//close file
		is.close();
		os.close();
	}
	void decompress(ifstream& is, ofstream& os)
	{
		//init
		vector<qNode*> qNodeTab;
		unsigned long long freq = 0;
		for(int i=0; i<256; i++)
		{
			is.read((char*)&freq, 8);
			//is >> freq;
			qNodeTab.push_back(new qNode(freq, new BinaryTreeNode<char>((char)i)));
		}

		//make code tree		
		BinaryTree<char>* hcTree = makeHuffmanCodeTree(qNodeTab);

		//make code table
		vector<bool> code[256];
		vector<bool> *codeBuffer = new vector<bool>;
		BinaryTreeNode<char> *cursor = hcTree->getRootPtr();
		codeTraverse(cursor, codeBuffer, code);

		//decode
		is.clear();
		is.seekg(0, ios::end);
		long fileSize = is.tellg();
		is.seekg(0x800, ios::beg);
		cursor = hcTree->getRootPtr();
		char c;
		list<bool> codeStream;
		while((long)is.tellg() != fileSize)
		{
			is.get(c);
			for(int i=0; i<8; i++)
			{
				if(c & (0x80>>i))
					codeStream.push_back(true);
				else
					codeStream.push_back(false);
			}
			while(!codeStream.empty())
			{
				if(!codeStream.front())
					cursor = cursor->getLeftChildPtr();
				else
					cursor = cursor->getRightChildPtr();
				codeStream.pop_front();

				if(cursor->isTerminal())
				{
					char cc = cursor->getData();
					os << cc;
					//os << cursor->getData();
					cursor = hcTree->getRootPtr();
				}
			}
		}

		//close file
		is.close();
		os.close();
	}
};

int main(int argc, char* argv[])
{
	ifstream inText, inZip;
	ofstream outText, outZip;
	HuffmanCodeZip hcz;
	char strBuff[256];

	if(argc == 3)
	{
		if(!strcmp(argv[1], "-c"))
		{
			inText.open(argv[2]);
			sprintf(strBuff, "%s.zip", argv[2]);
			outZip.open(strBuff, ios::binary);
			hcz.compress(inText, outZip);
		}
		else if(!strcmp(argv[1], "-d"))
		{
			inZip.open(argv[2], ios::binary);
			sprintf(strBuff, "%s.txt", argv[2]);
			outText.open(strBuff);
			hcz.decompress(inZip, outText);
		}
	}
	else
		cout << "invalid argument!\n -c [filename] : compress\n -d [filename] : decompress\n" << endl;
	return 0;
}
