#include <bits/stdc++.h>
#define MAX 10
using namespace std;
queue<int> deck; //牌堆
int numPlayer;	 //参与人数
int numZ = 0, numF = 0;
bool ifOver = 0;
struct character
{
	int hp = 4, id, index_player;				 //id为身份，index为玩家下标
	int ifEquip=0, ifExpose = 0, ifAlive = 1; //是否装备诸葛连弩、是否暴露、是否活着

	struct typeMP
	{						 //主公的特殊数据
		int statu[MAX] = {}; //对每个人的状态，0-未知，1-忠臣，2-类反，3-真反
		int firstEnemy = 0;

		int checkKill(bool ifKill)
		{
			if (ifKill) //如果杀死
				return player[firstEnemy].id;
			else
				return 0;
		}

		void updateEnemy() //	更新敌人
		{
			firstEnemy = 0;
			int Traget = 1;
			for (int i = 1; i < numPlayer; i++) //对其余玩家操作，循环n-1次
			{
				if (statu[i] >= 2 && player[i].ifAlive)
				{
					firstEnemy = i;
					break;
				}
			}
		}
	}MP;

	character(int id, int index_player) : id(id), index_player(index_player) {}

	struct typeCard //有关手牌的操作
	{
		vector<int> list; //存手牌
		struct typeDetCard
		{
			int reCard = 0, firstIndex;
		} detail[9]; //8种手牌分别剩余数量，最左的下标
		void init()	 //初始化手牌，抽四张
		{
			for (int i = 1; i <= 4; i++)
			{
				char t = getchar();
				while (t == ' ')
					t = getchar();
				int cardHash = hashCard(t);
				list.push_back(cardHash);
				if (!detail[cardHash].reCard++)
					detail[cardHash].firstIndex = list.size() - 1;
				break;
			}
		}
		void get(int n) //抽n张牌
		{
			while (n--)
			{
				list.push_back(deck.front());
				if (!detail[5].reCard++)
					detail[5].firstIndex = list.size() - 1;
				deck.pop();
			}
		}
		void del(int index_card) //删除index手牌，并更新firstIndex
		{
			int cardHash = list[index_card];
			list.erase(list.begin() + index_card);			   //删除
			if (--detail[cardHash].reCard)					   //拥有数--后仍有
				for (int i = index_card; i < list.size(); i++) //遍历寻找下一个最左侧的，小优化：从删除的index开始找
					if (cardHash == list[i])
					{
						detail[cardHash].firstIndex = i;
						break;
					}
		}
		void clear() //清空手牌和装备
		{
			list.clear();
			player[index_player].ifEquip = 0;
			memset(detail, 0, sizeof(detail));
		}

	private:
		int hashCard(char card) //将卡片字符哈希为数值
		{
			switch (card)
			{
			case 'P':
				return 1;
				break;
			case 'K':
				return 2;
				break;
			case 'D':
				return 3;
				break;
			case 'F':
				return 4;
				break;
			case 'N':
				return 5;
				break;
			case 'W':
				return 6;
				break;
			case 'J':
				return 7;
				break;
			case 'Z':
				return 8;
				break;
			}
		}
	} card;

	void initOP() //共同操作
	{
		if (hp < 4 && card.detail[1].reCard) //吃桃
		{
			hp++;
			card.del(card.detail[1].firstIndex);
		}
		while (card.detail[5].reCard) //南蛮
		{
			int Traget = index_player + 1;
			for (int i = 1; i < numPlayer; i++) //对其余玩家操作，循环n-1次
			{
				if (Traget > numPlayer) //从最后一位循环到第一位
					Traget = 1;
				player[Traget].passive(5);
			}
			card.del(card.detail[5].firstIndex);
		}
		while (card.detail[6].reCard) //万箭
		{
			int Traget = index_player + 1;
			for (int i = 1; i < numPlayer; i++) //对其余玩家操作，循环n-1次
			{
				if (Traget > numPlayer) //从最后一位循环到第一位
					Traget = 1;
				player[Traget].passive(6);
			}
			card.del(card.detail[6].firstIndex);
		}
		while (card.detail[8].reCard) //装备诸葛
		{
			ifEquip = 1;
			card.del(card.detail[8].firstIndex);
		}
	}

	void active() //主动操作
	{
		initOP();
		switch (id)
		{
		case 1:				   //主公
			if (MP.firstEnemy) //有敌人
			{
				if (card.detail[4].reCard) //有决斗
				{
					int cmd = MP.checkKill(player[MP.firstEnemy].passive(4, index_player));
					if (cmd != 0) //杀死了人
					{
						if (cmd == 2)  //杀死反贼
							if (!numF) //所有杀完
								break; //退出，准备输出
							else
								card.get(3);
						else
							card.clear();
						MP.updateEnemy();
					}
				}
			}
			break;
		case 2: //忠臣
			/* code */
			break;
		case 3: //反贼
			/* code */
			break;
		}
	}
	bool passive(int cmd, int actIndex_player) //被动操作，返回值是否被击杀
	{
		//如果死亡

		//被决斗

		//被杀
		//被南蛮
		//被万箭

		//被无懈
	}

private:
	void checkOver()
	{
		hp--;
	}
	int dist(int quesIndex_player)
	{
		int sum = 0;
		for (int tmpIndex_player = index_player + 1; tmpIndex_player != quesIndex_player; tmpIndex_player++)
		{
			if (tmpIndex_player > numPlayer)
				tmpIndex_player = 1;
			if (player[tmpIndex_player].hp)
				sum++;
		}
		return sum;
	}
} player[MAX + 1];

int main()
{
}