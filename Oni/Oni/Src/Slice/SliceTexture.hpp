#pragma once


#include "Linearly.hpp"
#include "Animation.hpp"


namespace Oni
{

	/// <summary>
	/// 1���̉摜�𕡐��̉摜�ɕ���,
	/// �؂�ւ��Ȃǂ��s����悤�ɂ���.
	/// </summary>
	class SliceTexture
	{
	private:

		// �摜�̖��O
		String mTextureName;

		// �摜��؂蕪����傫��
		Size mSliceSize;

		// true �̂Ƃ����E���]���ĕ`��
		bool mMirror;

		// �摜��J�ڂ��鎞��
		Linearly<double> mChangeSpan;

		// ���݂�Animation�̖��O
		String mAnimationName;

		// Animation���Ǘ�����}�b�v
		std::unordered_map<String, Animation> mAnimationMap;

	public:

		/// <summary>
		/// �摜�̐؂蕪��
		/// </summary>
		/// <param name="textureName"> �摜�̖��O             </param>
		/// <param name="sliceSize">   �摜��؂蕪����傫�� </param>
		/// <param name="pos">         �摜�̏����ԍ�         </param>
		SliceTexture(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// �摜�̖��O�̐ݒ�
		/// </summary>
		/// <param name="textureName"> �摜�̖��O             </param>
		/// <param name="sliceSize">   �摜��؂蕪����傫�� </param>
		void setTextureName(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// �A�j���[�V�����̐ݒ�
		/// </summary>
		/// <param name="anim"> �A�j���[�V���� </param>
		void setAnimation(const String& name, const Animation& anim)
		{
			mAnimationMap.try_emplace(name, anim);
		}

		/// <summary>
		/// �摜�̕ύX
		/// </summary>
		/// <returns>
		/// �摜�̐؂�ւ����I�������Ƃ� true , �����łȂ��Ƃ� false
		/// ���[�v���Ă���Ƃ��� true ����ɕԂ��̂Œ���
		/// </returns>
		bool update();

		/// <summary>
		/// �摜�̔��]
		/// </summary>
		void mirror()
		{
			mMirror = !mMirror;
		}

		/// <summary>
		/// �A�j���[�V�����̊J�n
		/// </summary>
		/// <param name="name"> �A�j���[�V�����̖��O </param>
		void start(const String name);

		/// <summary>
		/// �ʃA�j���[�V�����̊J�n
		/// </summary>
		/// <param name="name"> �A�j���[�V������ </param>
		void startAnotherAnimation(const String name);

		/// <summary>
		/// �摜�̕ύX
		/// </summary>
		TextureRegion getTexture() const;

	};
	
}