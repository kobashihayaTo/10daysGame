#include "UI.h"

void UI::Initialize()
{
}

void UI::Update()
{
}

void UI::Draw(int Number, int x, int y, int sprite_X, int sprite_Y, int spritew, int spriteh)
{

}

void UI::renderNumber(int Number, int num, int x, int y)
{
	const int max_num_digits = 8; // 最大桁数
	for (int i = max_num_digits; i >= 0; i--) {
		const int spritew = 16;  // スプライトの幅
		const int spriteh = 32;  // スプライトの高さ
		int base = 1;  // 基数、何桁目を描画しているかを計算
		for (int j = 0; j < i; j++)
			base *= 10;  // 10のi乗を計算、数学ライブラリをincludeするのが面倒だったのでforループで
		int digit = (num / base) % 10;  //これでi桁目の数字を[0, 9]の範囲として取得
		Draw(
			Number,  // 画像
			x + (max_num_digits - i) * spritew,  // 描画位置のx座標
			y,    // 描画位置のy座標
			spritew * digit,  // テクスチャ参照位置のx座標
			0,  // テクスチャ参照位置のy座標
			spritew,  // スプライトの幅
			spriteh);  // スプライトの高さ
	}
}
