#pragma once

enum class Scene {
	TITLE,//タイトル
	MANUAL,//マニュアル
	GAME,//ゲームシーン
	GAME2,//ゲームシーン2
	END,//エンド
	BADEND//ゲームオーバー
};

//map名をenumで規定
enum mapInfo {
	NONE,	//0
	BLOCK,	//1
	GOAL,    //2
	KUSO//3
};
