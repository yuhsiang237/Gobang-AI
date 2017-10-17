#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <string>
using namespace std;

class Board{
private:

	int ** board; //棋盤

public:
	int nowx,nowy,nowchess;	
	//取得棋盤位置分
	int getBoardPosScore(int x,int y){
		
		int position[15][15] = { 
	    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
	    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, 
	    { 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
	    { 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
	    { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 }, 
	    { 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 }, 
	    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, 
	    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	    return position[x][y];
	}

	//取得 - 
	string getHorizontal(int x,int y){
		string line = "";
		for(int i=4;i>=1;i--){
			if(isInSide(x,y-i)){
				line += to_string(board[x][y-i]);
			}
		}
		line+= to_string(board[x][y]);
		for(int i=1;i<=4;i++){
			if(isInSide(x,y+i)){
				line += to_string(board[x][y+i]);
			}
		}
		return line;
	}

	//取得 /
	string getLeftSlash(int x,int y){
		string line = "";
		for(int i=4;i>=1;i--){
			if(isInSide(x+i,y-i)){
				line += to_string(board[x+i][y-i]);
			}
		}
		line+= to_string(board[x][y]);
		for(int i=1;i<=4;i++){
			if(isInSide(x-i,y+i)){
				line += to_string(board[x-i][y+i]);
			}
		}
		return line;
	}
	//取得 \
	//
	string getRightSlash(int x,int y){
		string line = "";
		for(int i=4;i>=1;i--){
			if(isInSide(x-i,y-i)){
				line += to_string(board[x-i][y-i]);
			}
		}
		line+= to_string(board[x][y]);
		for(int i=1;i<=4;i++){
			if(isInSide(x+i,y+i)){
				line += to_string(board[x+i][y+i]);
			}
		}
		return line;
	}

	//取得 |
	string getVertical(int x,int y){
		string line = "";
		for(int i=4;i>=1;i--){
			if(isInSide(x-i,y)){
				line += to_string(board[x-i][y]);
			}
		}
		line+= to_string(board[x][y]);
		for(int i=1;i<=4;i++){
			if(isInSide(x+i,y)){
				line += to_string(board[x+i][y]);
			}
		}
		return line;
	}

	//判斷是否在邊界內
	bool isInSide(int x,int y){
		if(x >= 0 && x<15 && y>=0 && y<15){
			return true;
		}
		return false;
	}

	//複製新棋盤，並取代本來棋盤，此為避免C++ 參考關係才寫的函式
	void copyBoard(int ** newboard){
		for(int i=0;i<15;i++){
			for(int j=0;j<15;j++){
				board[i][j] = newboard[i][j];
			}
		}
	}

	//取得棋盤陣列
	int ** getBoardArr(){
		return board;
	}

	//畫出棋盤
	void showBoard(){
		cout<<setw(2)<<'-'<<' ';
		for(int i=0;i<15;i++){
			cout<<setw(2)<<i<<' ';
		}
		cout<<'\n';
		for(int i=0;i<15;i++){
			cout<<setw(2)<<i<<' ';
			for(int j=0;j<15;j++){
				cout<<setw(2)<<board[i][j]<<' ';
			}
			cout<<'\n';
		}
	}


	//依各種組合判斷給予的權重分數
	int getlineAllScore(int chess,int x,int y){

		//複製棋盤
		Board temp;
		temp.copyBoard(board);


		int line5 = 0; //長連
		
		int linelive4 = 0; //活四
		int linered4 =0;//衝四
		int linedead4 = 0;//死四

		int linelive3 = 0; //活三
		int lineSleep3 = 0;//眠三
		int linedead3 = 0;//死三
		int linelive3near = 0;//活三近

		int lineSleep2 = 0;//眠二
		int linelive2 = 0;//活二
		int linedead2 = 0;//死二


		string line[4];
		line[0] =  temp.getHorizontal(x,y);
		line[1] =  temp.getVertical(x,y);
		line[2] =  temp.getLeftSlash(x,y);
		line[3] =  temp.getRightSlash(x,y);

		for(int i=0;i<4;i++){
			//長連
			if( temp.isRegexLine(line[i],".*?11111.*?") ||
				 temp.isRegexLine(line[i],".*?22222.*?")
			){
		   		 //PLAYER分數
				line5++;
			}
			//活四
			if( temp.isRegexLine(line[i],".*?011110.*?") ||
				temp.isRegexLine(line[i],".*?022220.*?") 
				){
		   		linelive4++;
			}

			//衝四
			if( 
				temp.isRegexLine(line[i],".*?01111.*?") ||
				temp.isRegexLine(line[i],".*?02222.*?") ||
				temp.isRegexLine(line[i],".*?22202.*?") ||
				temp.isRegexLine(line[i],".*?11101.*?") ||
				temp.isRegexLine(line[i],".*?011112.*?") ||
				temp.isRegexLine(line[i],".*?0101110.*?")||
				temp.isRegexLine(line[i],".*?0110110.*?") ||
				temp.isRegexLine(line[i],".*?022221.*?") ||
				temp.isRegexLine(line[i],".*?0202220.*?") ||
				temp.isRegexLine(line[i],".*?0220220.*?") )
			{
				linered4++;
			}

			//死四
			if( temp.isRegexLine(line[i],".*?211112.*?") ||
				temp.isRegexLine(line[i],".*?122221.*?")){
				linedead4++;
			}


			//活三
			if(temp.isRegexLine(line[i],".*?01110.*?") ||
			   temp.isRegexLine(line[i],".*?010110.*?") ||
			   temp.isRegexLine(line[i],".*?02220.*?") ||
			   temp.isRegexLine(line[i],".*?020220.*?") 
			){

		
				linelive3++;
			}

			//眠三
			if(temp.isRegexLine(line[i],".*?001112.*?") ||
				temp.isRegexLine(line[i],".*?010112.*?") ||
				temp.isRegexLine(line[i],".*?011012.*?") ||
				temp.isRegexLine(line[i],".*?10011.*?") ||
				temp.isRegexLine(line[i],".*?10101.*?") ||
				temp.isRegexLine(line[i],".*?2011102.*?") ||
				temp.isRegexLine(line[i],".*?002221.*?") ||
				temp.isRegexLine(line[i],".*?020221.*?") ||
				temp.isRegexLine(line[i],".*?022021.*?") ||
				temp.isRegexLine(line[i],".*?20022.*?") ||
				temp.isRegexLine(line[i],".*?20202.*?") ||
				temp.isRegexLine(line[i],".*?1022201.*?") 
			){
				lineSleep3++;
			}

			//死三
			if( temp.isRegexLine(line[i],".*?21112.*?") ||
				 temp.isRegexLine(line[i],".*?12221.*?") 
				){
				linedead3++;
			}
			//活二
			if(temp.isRegexLine(line[i],".*?0110.*?") ||
				temp.isRegexLine(line[i],".*?01010.*?") ||
				temp.isRegexLine(line[i],".*?010010.*?") ||
				temp.isRegexLine(line[i],".*?0220.*?") ||
				temp.isRegexLine(line[i],".*?02020.*?") ||
				temp.isRegexLine(line[i],".*?020020.*?") 
			){
				linelive2++;
			}
			

			//眠二
			if(temp.isRegexLine(line[i],".*?000112.*?") ||
				temp.isRegexLine(line[i],".*?001012.*?") ||
				temp.isRegexLine(line[i],".*?010012.*?") ||
				temp.isRegexLine(line[i],".*?10001.*?") ||
				temp.isRegexLine(line[i],".*?2010102.*?") ||
				temp.isRegexLine(line[i],".*?2011002.*?") ||
				temp.isRegexLine(line[i],".*?000221.*?") ||
				temp.isRegexLine(line[i],".*?002021.*?") ||
				temp.isRegexLine(line[i],".*?020021.*?") ||
				temp.isRegexLine(line[i],".*?20002.*?") ||
				temp.isRegexLine(line[i],".*?1020201.*?") ||
				temp.isRegexLine(line[i],".*?1022001.*?") 
			){
				lineSleep2++;
			}

			//死二
			if(temp.isRegexLine(line[i],".*?2112.*?")||
			   temp.isRegexLine(line[i],".*?1221.*?")
			){
				linedead2++;
			}

			
		}

		int score = 0;
		//連五回傳100000;
		if(line5 >= 1){
			score = 100000;
		//活四回傳10000;
		}else if(linelive4 >= 1 || linered4 >=1){
			score = 10000;
		//衝四+活三
		}else if( linered4>=1 && linelive3 >=1 ){
			score = 10000;
		//雙活三回傳5000;
		}else if(linelive3 >=2 ){
			score = 5000;
		}
		//活三眠三
		else if(linelive3 >=1 && lineSleep3>=1){
			score = 1000;
		}
		//活三
		else if(linelive3 >=1 ){
			score = 200;
		//雙活二
		}else if(linelive2 >=1){
			score = 100;
		
		//眠三
		}else if(lineSleep3>=1){
			score = 50;
		
		//活二
		}else if(linelive2 >=1){
			score = 5;
		//眠二
		}else if(lineSleep2 >=1){
			score = 3;
		}

		return score;
	}
	//檢查是否遊戲結束
	bool isGameOver(int x,int y){
		if( isRegexLine(getVertical(x,y),".*?22222.*?") || 
			isRegexLine(getHorizontal(x,y),".*?22222.*?") || 
			isRegexLine(getRightSlash(x,y),".*?22222.*?") || 
			isRegexLine(getLeftSlash(x,y),".*?22222.*?") ||
			isRegexLine(getVertical(x,y),".*?11111.*?") || 
			isRegexLine(getHorizontal(x,y),".*?11111.*?") || 
			isRegexLine(getRightSlash(x,y),".*?11111.*?") || 
			isRegexLine(getLeftSlash(x,y),".*?11111.*?") 
		){
	   		 return true;
		}
		//如果還沒分出勝負
		return false;
	}

	//是否可以下子
	bool isChessCanDown(int x,int y){
		if(board[x][y] == 0){
			return true;
		}
		return false;
	}

	//強制設定棋子於棋盤
	bool setChessForced(int chess,int x,int y){
		this->nowx = x;
		this->nowy = y;
		this->nowchess = chess;
		board[x][y]  = chess;
		return true;
	
	}


	//設定棋子於棋盤
	bool setChess(int chess,int x,int y){
		if(board[x][y] == 0){
			this->nowx = x;
			this->nowy = y;
			this->nowchess = chess; 
			board[x][y]  = chess;
			return true;
		}
		return false;
	}
    Board(){
    	//初始化棋盤二維陣列為0
		board = new int*[15];
		for(int i=0;i<15;i++){
			board[i] = new int[15];
			for(int j=0;j<15;j++){
				board[i][j] = 0;
			}
		}
    }

    //判斷正則表達式
	bool isRegexLine(string line,string regstr){
	
		regex reg(regstr);
		string lineAsc	= line;
		string lineDesc	= line;

		reverse(lineDesc.begin(),lineDesc.end());

		if( regex_match(lineAsc, reg) || regex_match(lineDesc,reg)){
		   	return true;
		}
		return false;
	}

	//判斷是否棋盤都被下滿無法落子 被下滿則回傳true 反之
	bool isNoMove(){
		for(int i=0;i<15;i++){
			for(int j=0;j<15;j++){
				if(board[i][j] == 0){
					return false;
				}
			}
		}
		return true;
	}

	//找最佳步數
	Move bestMove(){

		Move move;
		move.x = -1;
		move.y = -1;
		move.score = -1e9;

		for(int i=0;i<15;i++){
			for(int j=0;j<15;j++){
				if(isChessCanDown(i,j)){		
					//攻擊分
					int attackScore = getlineAllScore(2,i,j);
					//防守分
					int defendScore = getlineAllScore(1,i,j);

					int sum = defendScore+attackScore+getBoardPosScore(i,j);
					
					//找出最大分
					if(sum > move.score){
						move.score  = sum;
						move.x = i;
						move.y = j;
					}
					
				}
			}
		}

		return move;
	}

	
};

