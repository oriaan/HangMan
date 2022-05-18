#include "Tries.h"
Tries::Tries()
{
	head = new Node();
}

void Tries::insert(std::string word)
{
	head->sub[word[0] - 65] = insert(head->sub[word[0] - 65], word, 0);
}

Node* Tries::insert(Node* node, std::string word, int pos)
{
	if (node == NULL)
	{
		Node* temp = new Node();
		if (pos == word.length() - 1)
		{
			temp->isWord = true;
			temp->n = 1;
			return temp;
		}
		temp->sub[word[pos + 1] - 65] = insert(temp->sub[word[pos + 1] - 65], word, pos + 1); 
		temp->n += temp->sub[word[pos + 1] - 65]->n;
		return temp;
	}
	
	if (pos == word.length() - 1)
	{
		node->isWord = true;
		node->n++;
		return node;
	}

	node->sub[word[pos + 1] - 65] = insert(node->sub[word[pos + 1] - 65], word, pos + 1);
	node->n += node->sub[word[pos + 1] - 65]->n;
	return node;
}