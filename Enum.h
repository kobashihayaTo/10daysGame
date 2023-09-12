#pragma once

enum class Scene {
	TITLE,			// タイトル
	MANUAL,			// マニュアル
	SELECT,			// ステージセレクト
	// 1ステージ
	Stage1GAME,		// ゲームシーン
	Stage1GAME2,	// ゲームシーン2
	// 2ステージ
	Stage2GAME,
	Stage2GAME2,
	// 3ステージ
	Stage3GAME,
	Stage3GAME2,

	END,			// エンド
	BADEND,			// ゲームオーバー
	CLEAR			// クリア
};

//map名をenumで規定
enum mapInfo {
	NONE,	// 0
	BLOCK,	// 1
	GOAL,	// 2
	DUMMY,	// 3
	WALL	// 4
};
