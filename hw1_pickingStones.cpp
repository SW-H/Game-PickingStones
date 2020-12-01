#include <stdio.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <stdlib.h>

struct Node
{
	float alpha = -1111.f;
	float beta = 1111.f;

	// 노드의 현재 깊이
	int curDepth = 0;
	// 돌을 의미
	int curStone = -1;
	// MaxPlayer의 턴인지 확인
	bool isMaxTurn = true;
	// 상위 NODE
	Node* rootNode;
	// 하위 NODE
	std::vector<Node*> nodes;
};

std::vector<int> fetchPossibleStones(int stone);
float evaluation(int stone, bool maxTurn);
void minimax(Node * rootNode);
Node* FindBestNode(Node* node);


// n은 최대 10000
#define MAX_STONE_NUM 10001

// n
int num_of_stones;
// 해당 숫자가 소수인 지 구할 수 있도록 미리 정리한 배열
bool num_is_prime_number[MAX_STONE_NUM];
// 돌의 상태 (0 : 가져오지 않은 상태, 1 : 가져 온 상태)
int stone_state[MAX_STONE_NUM];
// 최대 깊이
const int max_depth = 10;




int main(int argc, char** argv)
{

	int num_of_taken_stones;
	// 최상위 노드
	Node* rootNode = new Node();

	num_of_stones = atoi(argv[1]);
	num_of_taken_stones = atoi(argv[2]);

	for (int i = 0; i < num_of_taken_stones; ++i)
	{
		int stone;
		stone=atoi(argv[i+3]);
		stone_state[stone] = 1;
		rootNode->curStone = stone;
	}


	// MaxPlayer의 턴인지 아닌지 계산을 통해 가져옵니다.
	bool isMaxTurn = num_of_taken_stones % 2 == 0;

	// 소수인지에 대해 미리 정리합니다.
	memset(num_is_prime_number, true, sizeof(num_is_prime_number));
	for (int i = 3; i <= num_of_stones; ++i)
	{
		int sqr = (int)sqrt(i);
		for (int j = 2; j <= sqr; ++j)
		{
			if (i % j == 0)
			{
				num_is_prime_number[i] = false;
				break;
			}
		}
	}

	// 탐색 진행…
	rootNode->isMaxTurn = isMaxTurn;
	minimax(rootNode);

	Node* bestNode = FindBestNode(rootNode);
	Node* leafNode = rootNode;
	while (leafNode != FindBestNode(leafNode))
		leafNode = FindBestNode(leafNode);

	printf("Best Move : %d\n", bestNode->curStone);
	printf("Calculated Value : %.1f\n", bestNode->isMaxTurn ? bestNode->alpha : bestNode->beta);
	printf("Number of Visited Nodes : %d\n", leafNode->curDepth + 1);
	printf("Max Depth : %d\n", leafNode->curDepth);
}

//추가로 가져올 수 있는 돌을 계산합니다
std::vector<int> fetchPossibleStones(int stone)
{
	std::vector<int> stones;
	// 첫 번째 플레이어인 경우 -1 로 들어옵니다.
	if (stone == -1)
	{
		for (int i = 1; i <= num_of_stones / 2; ++i)
		{
			if (i % 2 != 0)
				stones.push_back(i);
		}
	}
	else
	{
		for (int i = 1; i <= stone; ++i)
		{
			if (stone % i == 0)
			{
				if (stone_state[i] == 0)
				{
					stones.push_back(i);
				}
			}
		}
		for (int i = 2;; ++i)
		{
			if (stone * i > num_of_stones)
				break;

			if (stone_state[stone * i] == 0)
				stones.push_back(stone * i);
		}
	}

	return stones;
}

//이익계산하여 alpha, beta 를 결정합니다.
float evaluation(int stone, bool maxTurn)
{
	if (stone_state[1] == 0)
		return 0.0f;

	int count = 0;
	float retValue = 0.0f;

	if (stone == 1)
	{
		for (int i = 2; i <= num_of_stones; ++i)
		{
			if (stone_state[i] == 0)
				++count;
		}
		retValue = 0.5f;
	}
	else if (num_is_prime_number[stone])
	{
		for (int i = 2;; ++i)
		{
			if (stone * i > num_of_stones)
				break;
			if (stone_state[stone * i] == 0)
				++count;
		}
		retValue = 0.7f;
	}
	else
	{
		for (int i = 1; i <= stone; ++i)
		{
			if (stone % i == 0)
			{
				if (stone_state[i] == 0)
				{
					++count;
				}
			}
		}
		retValue = 0.6f;
	}

	if (count == 0)
		return maxTurn ? -1.0f : 1.0f;

	if (count % 2 == 1)
		return maxTurn ? retValue : -retValue;

	return maxTurn ? -retValue : retValue;
}


void minimax(Node * rootNode)
{

	if (rootNode->curStone != -1)
		stone_state[rootNode->curStone] = 1;

	// 가져올 수 있는 돌들의 목록을 가져옵니다.
	auto numbers = fetchPossibleStones(rootNode->curStone);
	if (numbers.size() == 0 || rootNode->curDepth == max_depth)
	{
		rootNode->alpha = rootNode->beta = evaluation(rootNode->curStone, rootNode->isMaxTurn);
		stone_state[rootNode->curStone] = 0;
		return;
	}


	// 탐색, 이익계산, 가지치기 진행합니다.
	for (auto number : numbers)
	{
		Node* subNode = new Node();
		subNode->curDepth = rootNode->curDepth + 1;
		subNode->curStone = number;
		subNode->rootNode = rootNode;
		subNode->isMaxTurn = !rootNode->isMaxTurn;
		rootNode->nodes.push_back(subNode);

		minimax(subNode);
		if (rootNode->isMaxTurn)
		{
			if (subNode->beta >= rootNode->beta)
			{
				return;
			}
			if (subNode->beta > rootNode->alpha)
			{
				rootNode->alpha = subNode->beta;
			}
		}
		else if (!rootNode->isMaxTurn)
		{
			if (rootNode->beta <= rootNode->alpha)
			{
				return;
			}
			if (subNode->alpha < rootNode->beta)
			{
				rootNode->beta = subNode->alpha;
			}
		}
	}

	if (rootNode->curStone != -1)
		stone_state[rootNode->curStone] = 0;
}

//다음 노드의 최선 값(Best Move)을 가져옵니다.
Node* FindBestNode(Node* node)
{
	float v1, v2;
	if (node->isMaxTurn)
		v1 = node->alpha;
	else
		v1 = node->beta;

	for (auto childNode : node->nodes)
	{
		if (childNode->isMaxTurn)
			v2 = childNode->alpha;
		else
			v2 = childNode->beta;

		if (v1 == v2)
			return childNode;
	}

	return node;
}


