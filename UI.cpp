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
	const int max_num_digits = 8; // �ő包��
	for (int i = max_num_digits; i >= 0; i--) {
		const int spritew = 16;  // �X�v���C�g�̕�
		const int spriteh = 32;  // �X�v���C�g�̍���
		int base = 1;  // ��A�����ڂ�`�悵�Ă��邩���v�Z
		for (int j = 0; j < i; j++)
			base *= 10;  // 10��i����v�Z�A���w���C�u������include����̂��ʓ|�������̂�for���[�v��
		int digit = (num / base) % 10;  //�����i���ڂ̐�����[0, 9]�͈̔͂Ƃ��Ď擾
		Draw(
			Number,  // �摜
			x + (max_num_digits - i) * spritew,  // �`��ʒu��x���W
			y,    // �`��ʒu��y���W
			spritew * digit,  // �e�N�X�`���Q�ƈʒu��x���W
			0,  // �e�N�X�`���Q�ƈʒu��y���W
			spritew,  // �X�v���C�g�̕�
			spriteh);  // �X�v���C�g�̍���
	}
}
