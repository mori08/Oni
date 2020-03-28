#include "RecordManager.hpp"
#include "../MyLibrary.hpp"


namespace
{
	// ���R�[�h��ۑ�����t�@�C����
	const String RECORD_TEXT_NAME = U"SAVE_DATA.txt";

	constexpr int32 BASE    = 0x10;      // �Í����̊�ɂȂ�l(���i���ňÍ������邩)
	constexpr int32 MUL     = BASE - 1;  // �|���Z�̂Ƃ��̂����鐔
	constexpr int32 HALF    = BASE / 2;  // ��l�̔���
	constexpr int32 MOD     = BASE*BASE; // �]����Ƃ�Ƃ��̊��鐔 
	constexpr int32 MAX_KEY = MOD - 1;   // ���̍ő�l

	// �Í����ɂ�����1�f�[�^�̂Ƃ镶����
	constexpr int32 ONE_DATA_LENGTH = 2;
}


namespace Oni
{
	
	RecordManager::RecordManager()
	{
		mRecordMap.try_emplace(U"TestFlag" , std::move(Record(1, 0)));
		mRecordMap.try_emplace(U"TestValue", std::move(Record(3, 5)));
	}


	RecordManager::LoadResult RecordManager::load()
	{
		TextReader reader(RECORD_TEXT_NAME);

		// RECORD.txt�����݂��Ȃ��Ƃ� NEWGAME
		if (!reader)
		{
			initAllRecord();
			return LoadResult::NEW_GAME;
		}

		String line;

		if (reader.readLine(line) && decryption(line))
		{
			// �����ł����� CONTINUE
			return LoadResult::CONTINUE;
		}

		return LoadResult::ERROR;
	}


	void RecordManager::initAllRecord()
	{
		for (auto& record : mRecordMap)
		{
			record.second.init();
		}
	}


	void RecordManager::save()
	{
		TextWriter writer(RECORD_TEXT_NAME);

		writer.write(encryption());
	}


	void RecordManager::printAllRecord()
	{
#ifdef _DEBUG

		ClearPrint();
		int32 cnt = 0;
		String text;
		for (auto& record : mRecordMap)
		{
			text += U"[" + record.first + U" : " + ToString(record.second.get()) + U"]";

			if (++cnt % 3 == 0) { Print << text; text = U""; }
		}

#endif // _DEBUG
	}


	void RecordManager::setRecord(const String& name, int32 value)
	{
		if (!mRecordMap.count(name))
		{
			printDebug(U"[RecordManager::setRecord]");
			printDebug(U"�o�^����Ă��Ȃ����R�[�h�ł�");
			printDebug(U"name > " + name);
			return;
		}

		mRecordMap.find(name)->second.set(value);
	}


	int32 RecordManager::getRecord(const String& name) const
	{
		if (!mRecordMap.count(name))
		{
			printDebug(U"[RecordManager::setRecord]");
			printDebug(U"�o�^����Ă��Ȃ����R�[�h�ł�");
			printDebug(U"name > " + name);
			return 0;
		}

		return mRecordMap.find(name)->second.get();
	}


	String RecordManager::encryption() const
	{
		// �Í��p�̃��X�g
		std::list<int32> dataList;

		// �e���R�[�h���� 0 1 �̃��X�g��ǉ�
		for (const auto& record : mRecordMap)
		{
			record.second.addRecordToEncryptionList(dataList);
		}

		// 0 -> [0x2,0x10]�͈̔͂̋���
		// 1 -> [0x1,0xF] �͈̔͂̊
		for (auto& data : dataList)
		{
			data = 2 * (Random(0x1, HALF)) - data;
		}

		// �S�Ă�0xF������
		for (auto& data : dataList)
		{
			data *= MUL;
		}

		// ���𐶐����� 
		int32 key = Random(0x0, MAX_KEY);

		// ���X�g�̐擪�Ɩ����Ɍ���ǉ�
		dataList.emplace_front(key);
		dataList.emplace_back(key);

		// �O�̍��̒l�� mod 0x100 �ŉ��Z
		int32 previousOne = 0;
		for (auto& data : dataList)
		{
			data = (data + previousOne) % MOD;
			previousOne = data;
		}

		// �����l�̔z�� -> ������
		String rtn;
		for (const auto& data : dataList)
		{
			rtn += Pad(U"{:x}"_fmt(data), { ONE_DATA_LENGTH, U'0' });
		}

		return std::move(rtn);
	}


	bool RecordManager::decryption(const String& str)
	{
		// �����p�̃��X�g
		std::list<int32> dataList;

		// ������ -> �����l�̔z��
		for (size_t i = 0; i < str.length(); i += ONE_DATA_LENGTH)
		{
			auto data = ParseIntOpt<int32>(str.substr(i, ONE_DATA_LENGTH), Arg::radix = BASE);
			if (!data)
			{
				return false; // �ϊ��ł��Ȃ��Ƃ����s
			}
			dataList.emplace_back(*data);
		}

		// �O�̍��̒l�� mod 0x100 �� ���Z
		int32 previouseOne = 0;
		for (auto& data : dataList)
		{
			int32 temp = data;
			data = (data - previouseOne + MOD) % MOD;
			previouseOne = temp;
		}

		// �擪�E�����̌����폜
		if (*dataList.begin() != *dataList.rbegin())
		{
			return false; // ������v���Ȃ��Ƃ����s
		}
		dataList.pop_front();
		dataList.pop_back();

		// �T�C�Y �� ���R�[�h�̍��v���� ����v���Ă��邩�m�F
		if (dataList.size() != Record::getDigitTotal())
		{
			return false; // ��v���Ȃ��Ƃ����s
		}

		// �S�Ă�0xF�Ŋ���
		for (auto& data : dataList)
		{
			if (data % MUL != 0)
			{
				return false; // ����؂�Ȃ��Ƃ����s
			}
			data /= MUL;
			if (data <= 0x0 || data > BASE)
			{
				return false; // [0x1,0x10]�͈̔͂ɂȂ��Ƃ����s
			}
		}

		// ���� -> 0
		// � -> 1
		for (auto& data : dataList)
		{
			data %= 2;
		}

		// ���R�[�h�Ɋi�[
		for (auto& record : mRecordMap)
		{
			record.second.setValueFromDecryption(dataList);
		}

		return true;
	}

}
