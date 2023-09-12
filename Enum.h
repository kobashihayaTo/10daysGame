#pragma once

enum class Scene {
	TITLE,			// �^�C�g��
	MANUAL,			// �}�j���A��
	SELECT,			// �X�e�[�W�Z���N�g
	// 1�X�e�[�W
	Stage1GAME,		// �Q�[���V�[��
	Stage1GAME2,	// �Q�[���V�[��2
	// 2�X�e�[�W
	Stage2GAME,
	Stage2GAME2,
	// 3�X�e�[�W
	Stage3GAME,
	Stage3GAME2,

	END,			// �G���h
	BADEND,			// �Q�[���I�[�o�[
	CLEAR			// �N���A
};

//map����enum�ŋK��
enum mapInfo {
	NONE,	// 0
	BLOCK,	// 1
	GOAL,	// 2
	DUMMY,	// 3
	WALL	// 4
};
