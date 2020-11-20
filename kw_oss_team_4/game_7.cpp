#include "game.h"

using namespace std;
using namespace sf;



short userID = 1;
short roundNumber = 0;
bool gameover = false;

short playerScore = 0, comScore = 0;

short mapWidth = 600;
short mapHeight = 600;

short cellSize = 200;

short characterSize = 32;

short a[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
};
unsigned short maptrix[3][3][2]{
	{{0,16},{200,16},{400,16}},
	{{0,216},{200,216},{400,216}},
	{{0,416},{200,416},{400,416}},
};


// UI
sf::Text roundNumberText;
sf::Text playerText;
sf::Text comText;

sf::Vector2f mouseposition;
bool mousecontrol(sf::Vector2f pointerPosition, short usrID);
void elReset(short stateMatrix[3][3]);
bool endControl(short stateMatrix[3][3], short userID);
bool drwaControl();

sf::Font font;
sf::Font fonttictactoe(string fontPath);

void gamewindow(sf::RenderWindow* window);

sf::Text temizle(float x, float y, string metin);
sf::Text xCiz(float x, float y);
sf::Text oCiz(float x, float y);

void main_game_7(int dif, int pr)
{
	
	sf::RenderWindow window(sf::VideoMode(mapWidth, mapHeight + 50), "Tic-Tac-Toe", sf::Style::Close);//sf::Style::Fullscreen
	window.setFramerateLimit(30);
	font = fonttictactoe("neuropol.ttf");

	while (window.isOpen())
	{
		sf::Event event;

		mouseposition = sf::Vector2f();

		if (gameover) {
			//점수 리셋 
		}
		window.clear(sf::Color(0, 0, 0));
		gamewindow(&window);
		// 인풋 컨트롤 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) { // 스크린의 X버튼을 누르거나, 혹은 키보드의 ESC를 누르면 메인화면으로 돌아가도록 수정
				window.close();
				if (pr == 1) {
					practice(dif);
				}
				else {
					//main(1); // 메인화면 창을 다시 열기
					main_difficulty();
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				mouseposition = sf::Vector2f(event.touch.x, event.touch.y);
				if (mousecontrol(mouseposition, userID)) {
					cout << userID << endl;
					if (userID == 1) {
						if (endControl(a, userID)) { // 이겼을때 체크 
							playerScore += 1;
							if (!(playerScore >= 5)) {
								elReset(a); // 판 초기화 
								roundNumber++;
							}
							else { // 5번이기면 종료
								//승리의 사운드 추가?
								window.close();
								if (pr == 1) {
									practice(dif);
								}
								break;
							}
						}
						else if (drwaControl()) { // 빈칸 없으면 false 
							elReset(a);
							roundNumber++;
						}
						userID = 2;
						if (userID == 2) {
							if (endControl(a, userID)) {
								comScore += 1;
								if (!(comScore >= 5)) {
									elReset(a);
									roundNumber++;
								}
								else {
									failsound();
									sf::sleep(sf::seconds(1.5f));
									window.close();
									if (pr == 1) {
										practice(dif);
									}
									break;
								}
							}
							else if (drwaControl()) {
								elReset(a);
								roundNumber++;
							}
							userID = 1;
						}
					}
				}
			}
		}


		window.display();
	}
	
}
void gamewindow(sf::RenderWindow* window) {
	// background
	short count = 0;
	for (short x = 0; x < 3; x++) {
		for (short y = 0; y < 3; y++) {
			sf::RectangleShape kare;
			kare.setSize(sf::Vector2f(cellSize, cellSize));
			kare.setPosition(x * cellSize, y * cellSize + 50);
			kare.setFillColor(sf::Color::Black);
			kare.setOutlineThickness(2.0f);
			kare.setOutlineColor(sf::Color::White);
			window->draw(kare);
			count++;
		}
	}
	// background
	// UI
	roundNumberText.setFont(font);
	roundNumberText.setPosition(mapWidth / 2 - characterSize / 2 - 40, 5);
	roundNumberText.setCharacterSize(characterSize);
	roundNumberText.setFillColor(sf::Color::White);
	roundNumberText.setString(" - " + to_string(roundNumber) + " - ");

	playerText.setFont(font);
	playerText.setPosition(10, 5);
	playerText.setCharacterSize(characterSize);
	playerText.setFillColor(sf::Color::White);

	comText.setFont(font);
	comText.setPosition(mapWidth - 200, 5);
	comText.setCharacterSize(characterSize);
	comText.setFillColor(sf::Color::White);

	if (userID == 1) {
		playerText.setString("->X = " + to_string(playerScore));
	}
	else {
		playerText.setString("X = " + to_string(playerScore));
	}
	if (userID == 2) {
		comText.setString("->AI = " + to_string(comScore));
	}
	else {
		comText.setString("AI = " + to_string(comScore));
	}

	window->draw(roundNumberText);
	window->draw(playerText);
	window->draw(comText);

	// ./UI

	// 	game drawing
	for (short y = 0; y < 3; y++) {
		for (short x = 0; x < 3; x++) {
			if (a[x][y] == 1) {
				window->draw(xCiz(maptrix[x][y][0], maptrix[x][y][1]));
			}
			else if (a[x][y] == 2) {
				window->draw(oCiz(maptrix[x][y][0], maptrix[x][y][1]));
			}
			else {
				window->draw(temizle(maptrix[x][y][0], maptrix[x][y][1], " "));
			}
		}
	}
	// game drawing
}
void secondturn() {
	short usrID = 2;
	time_t t;

	time(&t);
	srand((unsigned int)t);

	for (int i = 0; i <= 200; i++) {

		int m = (rand() + 8) % 3;
		int n = (rand() + 8) % 3;

		if ((a[0][0] == usrID) && (a[0][1] == usrID) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; }
		if ((a[1][0] == usrID) && (a[1][1] == usrID) && (a[1][2] != usrID - 1) && (a[1][2] != usrID)) { a[1][2] = usrID; break; }
		if ((a[2][0] == usrID) && (a[2][1] == usrID) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID) && (a[0][2] == usrID) && (a[0][1] != usrID - 1) && (a[0][1] != usrID)) { a[0][1] = usrID; break; }
		if ((a[1][0] == usrID) && (a[1][2] == usrID) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[2][0] == usrID) && (a[2][2] == usrID) && (a[2][1] != usrID - 1) && (a[2][1] != usrID)) { a[2][1] = usrID; break; }
		if ((a[0][1] == usrID) && (a[0][2] == usrID) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; }
		if ((a[1][1] == usrID) && (a[1][2] == usrID) && (a[1][0] != usrID - 1) && (a[1][0] != usrID)) { a[1][0] = usrID; break; }
		if ((a[2][1] == usrID) && (a[2][2] == usrID) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; } //가로줄 조건

		if ((a[0][0] == usrID) && (a[1][0] == usrID) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; }
		if ((a[0][1] == usrID) && (a[1][1] == usrID) && (a[2][1] != usrID - 1) && (a[2][1] != usrID)) { a[2][1] = usrID; break; }
		if ((a[0][2] == usrID) && (a[1][2] == usrID) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID) && (a[2][0] == usrID) && (a[1][0] != usrID - 1) && (a[1][0] != usrID)) { a[1][0] = usrID; break; }
		if ((a[0][1] == usrID) && (a[2][1] == usrID) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[0][2] == usrID) && (a[2][2] == usrID) && (a[1][2] != usrID - 1) && (a[1][2] != usrID)) { a[1][2] = usrID; break; }
		if ((a[1][0] == usrID) && (a[2][0] == usrID) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; }
		if ((a[1][1] == usrID) && (a[2][1] == usrID) && (a[0][1] != usrID - 1) && (a[0][1] != usrID)) { a[0][1] = usrID; break; }
		if ((a[1][2] == usrID) && (a[2][2] == usrID) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; } //세로줄 조건

		if ((a[0][0] == usrID) && (a[1][1] == usrID) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID) && (a[2][2] == usrID) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[1][1] == usrID) && (a[2][2] == usrID) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; } // 대각조건

		if ((a[0][2] == usrID) && (a[1][1] == usrID) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; }
		if ((a[0][2] == usrID) && (a[2][0] == usrID) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[1][1] == usrID) && (a[2][0] == usrID) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; } //왼아래 대각



		if ((a[0][0] == usrID - 1) && (a[0][1] == usrID - 1) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; }
		if ((a[1][0] == usrID - 1) && (a[1][1] == usrID - 1) && (a[1][2] != usrID - 1) && (a[1][2] != usrID)) { a[1][2] = usrID; break; }
		if ((a[2][0] == usrID - 1) && (a[2][1] == usrID - 1) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID - 1) && (a[0][2] == usrID - 1) && (a[0][1] != usrID - 1) && (a[0][1] != usrID)) { a[0][1] = usrID; break; }
		if ((a[1][0] == usrID - 1) && (a[1][2] == usrID - 1) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[2][0] == usrID - 1) && (a[2][2] == usrID - 1) && (a[2][1] != usrID - 1) && (a[2][1] != usrID)) { a[2][1] = usrID; break; }
		if ((a[0][1] == usrID - 1) && (a[0][2] == usrID - 1) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; }
		if ((a[1][1] == usrID - 1) && (a[1][2] == usrID - 1) && (a[1][0] != usrID - 1) && (a[1][0] != usrID)) { a[1][0] = usrID; break; }
		if ((a[2][1] == usrID - 1) && (a[2][2] == usrID - 1) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; }

		if ((a[0][0] == usrID - 1) && (a[1][0] == usrID - 1) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; }
		if ((a[0][1] == usrID - 1) && (a[1][1] == usrID - 1) && (a[2][1] != usrID - 1) && (a[2][1] != usrID)) { a[2][1] = usrID; break; }
		if ((a[0][2] == usrID - 1) && (a[1][2] == usrID - 1) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID - 1) && (a[2][0] == usrID - 1) && (a[1][0] != usrID - 1) && (a[1][0] != usrID)) { a[1][0] = usrID; break; }
		if ((a[0][1] == usrID - 1) && (a[2][1] == usrID - 1) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[0][2] == usrID - 1) && (a[2][2] == usrID - 1) && (a[1][2] != usrID - 1) && (a[1][2] != usrID)) { a[1][2] = usrID; break; }
		if ((a[1][0] == usrID - 1) && (a[2][0] == usrID - 1) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; }
		if ((a[1][1] == usrID - 1) && (a[2][1] == usrID - 1) && (a[0][1] != usrID - 1) && (a[0][1] != usrID)) { a[0][1] = usrID; break; }
		if ((a[1][2] == usrID - 1) && (a[2][2] == usrID - 1) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; }

		if ((a[0][0] == usrID - 1) && (a[1][1] == usrID - 1) && (a[2][2] != usrID - 1) && (a[2][2] != usrID)) { a[2][2] = usrID; break; }
		if ((a[0][0] == usrID - 1) && (a[2][2] == usrID - 1) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[1][1] == usrID - 1) && (a[2][2] == usrID - 1) && (a[0][0] != usrID - 1) && (a[0][0] != usrID)) { a[0][0] = usrID; break; }

		if ((a[0][2] == usrID - 1) && (a[1][1] == usrID - 1) && (a[2][0] != usrID - 1) && (a[2][0] != usrID)) { a[2][0] = usrID; break; }
		if ((a[0][2] == usrID - 1) && (a[2][0] == usrID - 1) && (a[1][1] != usrID - 1) && (a[1][1] != usrID)) { a[1][1] = usrID; break; }
		if ((a[1][1] == usrID - 1) && (a[2][0] == usrID - 1) && (a[0][2] != usrID - 1) && (a[0][2] != usrID)) { a[0][2] = usrID; break; } //방어조건들

		if ((a[m][n] != usrID - 1) && (a[m][n] != usrID)) { a[m][n] = usrID; break; } // 인공지능 첫돌
	}
}
bool mousecontrol(sf::Vector2f pointerPosition, short usrID) { // 입력단 

	if (userID == 1) {
		if ((pointerPosition.x < 200 and pointerPosition.x > 0) and (pointerPosition.y <= 250 and pointerPosition.y > 50)) {//x=0, y=0.cell
			if (a[0][0] == 0) {
				a[0][0] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 400 and pointerPosition.x > 200) and (pointerPosition.y <= 250 and pointerPosition.y > 50)) {
			if (a[0][1] == 0) {
				a[0][1] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 600 and pointerPosition.x > 400) and (pointerPosition.y <= 250 and pointerPosition.y > 50)) {
			if (a[0][2] == 0) {
				a[0][2] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 200 and pointerPosition.x > 0) and (pointerPosition.y <= 450 and pointerPosition.y > 250)) {
			if (a[1][0] == 0) {
				a[1][0] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 400 and pointerPosition.x > 200) and (pointerPosition.y <= 450 and pointerPosition.y > 250)) {
			if (a[1][1] == 0) {
				a[1][1] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 600 and pointerPosition.x > 400) and (pointerPosition.y <= 450 and pointerPosition.y > 250)) {
			if (a[1][2] == 0) {
				a[1][2] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 200 and pointerPosition.x > 0) and (pointerPosition.y <= 650 and pointerPosition.y > 450)) {
			if (a[2][0] == 0) {
				a[2][0] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 400 and pointerPosition.x > 200) and (pointerPosition.y <= 650 and pointerPosition.y > 450)) {
			if (a[2][1] == 0) {
				a[2][1] = usrID;
				secondturn();
				return true;
			}
		}
		else if ((pointerPosition.x < 600 and pointerPosition.x > 400) and (pointerPosition.y <= 650 and pointerPosition.y > 450)) {
			if (a[2][2] == 0) {
				a[2][2] = usrID;
				secondturn();
				return true;
			}
		}
	}


	return false;
}
void elReset(short stateMatrix[3][3]) {
	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{
			stateMatrix[i][j] = 0;
		}
	}
}

bool endControl(short stateMatrix[3][3], short userIDParam) { //
	if (stateMatrix[0][0] == userIDParam and stateMatrix[0][1] == userIDParam and stateMatrix[0][2] == userIDParam) {
		return true; //  1.가로
	}
	if (stateMatrix[1][0] == userIDParam and stateMatrix[1][1] == userIDParam and stateMatrix[1][2] == userIDParam) {
		return true; // 2.
	}
	if (stateMatrix[2][0] == userIDParam and stateMatrix[2][1] == userIDParam and stateMatrix[2][2] == userIDParam) {
		return true; // 3.
	}
	if (stateMatrix[0][0] == userIDParam and stateMatrix[1][0] == userIDParam and stateMatrix[2][0] == userIDParam) {
		return true; // 1.세로 
	}
	if (stateMatrix[0][1] == userIDParam and stateMatrix[1][1] == userIDParam and stateMatrix[2][1] == userIDParam) {
		return true; // 2.
	}
	if (stateMatrix[0][2] == userIDParam and stateMatrix[1][2] == userIDParam and stateMatrix[2][2] == userIDParam) {
		return true; // 3.
	}
	if (stateMatrix[0][0] == userIDParam and stateMatrix[1][1] == userIDParam and stateMatrix[2][2] == userIDParam) {
		return true; // Cross left top - bottom right
	}
	if (stateMatrix[2][0] == userIDParam and stateMatrix[1][1] == userIDParam and stateMatrix[0][2] == userIDParam) {
		return true;
	}
	return false;
}
bool drwaControl() {
	bool drawdraw = true;
	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{
			if (a[i][j] == 0) {
				drawdraw = false; // 빈칸없으면 
			}
		}
	}
	return drawdraw;
}
sf::Text xCiz(float x, float y) {
	sf::Text metinX;
	metinX.setFont(font);
	metinX.setPosition(x, y);
	metinX.setFillColor(sf::Color::White);
	metinX.setCharacterSize(cellSize);
	metinX.setString("X");
	return metinX;
}
sf::Text oCiz(float x, float y) {
	sf::Text metinO;
	metinO.setFont(font);
	metinO.setPosition(x, y);
	metinO.setFillColor(sf::Color::White);
	metinO.setCharacterSize(cellSize);
	metinO.setString("O");
	return metinO;
}
sf::Text temizle(float x, float y, string metin) {
	sf::Text mainText;
	mainText.setFont(font);
	mainText.setPosition(x, y);
	mainText.setFillColor(sf::Color::Black);
	mainText.setCharacterSize(cellSize);
	mainText.setString(metin);
	return mainText;
}
sf::Font fonttictactoe(string fontPath) {
	sf::Font fontNeuropol;
	if (!fontNeuropol.loadFromFile(fontPath)) {
		cout << "폰트 정상 로드 안됨!";
	}
	return fontNeuropol;
}
