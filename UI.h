#pragma once
class UI
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="player"> プレイヤー </param>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="block"></param>
	/// <param name="goal"></param>
	void Draw(int Number, int x, int y, int sprite_X, int sprite_Y, int spritew, int spriteh); // ここでmainブロック画像をもってきてる

	void renderNumber(int Number, int num, int x, int y);
};

