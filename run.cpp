#include <iostream>
#include <iomanip>
#include "Move.h"
#include "Board.h"

using namespace std;


int main(){

	//建立一個盤面
	Board b;
	//玩家下棋的座標
	int x,y;
	//回合數
	int count = 0 ;
	//無窮迴圈直到一方勝出或平均
	while(1){
		cout<<"===   第"<<++count<<"回合   ==="<<endl;
		cout<<"請輸入 x y 座標"<<endl;
		cin>>x>>y;
		//玩家下棋
		b.setChess(1,x,y);	
		//顯示玩家下過的棋盤
		cout<<"PLAYER:"<<endl;
		b.showBoard();

		//如果此次下完終局表示玩家勝出
		if(b.isGameOver(x,y)){
			cout<<"PLAYER WIN"<<endl;
			break;
		}
		//如果沒有辦法再落子則離開迴圈 平局
		if(b.isNoMove()){
			cout<<"TIE"<<endl;
			break;
		}
		//AI下棋
		Move move = b.bestMove();
		cout<<"AI分析權重結果"<<"\nx:"<<move.x<<"\t"<<"y:"<<move.y<<"\tscore:"<<move.score<<endl;
		
		b.setChess(2,move.x,move.y);
		cout<<"AI:"<<endl;
		//顯示AI下完的棋盤 與 x y 座標 權重
		b.showBoard();
		//如果此次下完終局表示AI勝出
		if(b.isGameOver(move.x,move.y)){
			cout<<"AI WIN"<<endl;
			break;
		}
		//如果沒有辦法再落子則離開迴圈 平局
		if(b.isNoMove()){
			cout<<"TIE"<<endl;
			break;
		}
		
	}
}