#pragma once
class UI
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player"> �v���C���[ </param>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="block"></param>
	/// <param name="goal"></param>
	void Draw(int Number, int x, int y, int sprite_X, int sprite_Y, int spritew, int spriteh); // ������main�u���b�N�摜�������Ă��Ă�

	void renderNumber(int Number, int num, int x, int y);
};

